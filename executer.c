/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 15:37:17 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/02 16:04:38 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_exec.h"

void	redirect_input(char *file_name, int type)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE); // file does not exist
	if (dup2(fd, STDIN_FILENO) < 0)
		exit(EXIT_FAILURE); // dup fail
	close(fd);
	if (type == T_HEREDOC)
		free(file_name);
}

void	redirect_output(char *file_name)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (access(file_name, W_OK) < 0)
		exit(EXIT_FAILURE); // file write fail
	if (fd < 0)
		exit(EXIT_FAILURE); // file does not exist
	if (dup2(fd, STDOUT_FILENO) < 0)
		exit(EXIT_FAILURE); // dup fail
	close(fd);
}

void	redirect_heredoc(char **deli, int cnt)
{
	char	*tmp_file;
	char	*str_cnt;
	int		fd;
	char	*buf;

	str_cnt = ft_itoa(cnt);
	if (!str_cnt)
		exit(EXIT_FAILURE);
	tmp_file = ft_strjoin(".heredoc", str_cnt);
	if (!tmp_file)
		exit(EXIT_FAILURE);
	free(str_cnt);
	fd = open(tmp_file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		exit(EXIT_FAILURE);
	while (1)
	{
		buf = readline("> ");
		if (buf && ft_strncmp(buf, *deli, ft_strlen(*deli) + 1) != 0)
		{
			write(fd, buf, ft_strlen(buf));
			write(fd, "\n", 1);
			free(buf);
		}
		else
			break;
	}
	*deli = tmp_file;
	free(buf);
	close(fd);
}

void	redirect_append(char *file_name)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (access(file_name, W_OK) < 0)
		exit(EXIT_FAILURE); // file write fail
	if (fd < 0)
		exit(EXIT_FAILURE); // file does not exist
	if (dup2(fd, STDOUT_FILENO) < 0)
		exit(EXIT_FAILURE); // dup fail
	close(fd);
}

void	exit_malloc_error(void)
{
	const char	*err_str = "Malloc Error";

	write(2, err_str, ft_strlen(err_str));
}

int	get_pipe_size(t_pipe_node *head)
{
	t_pipe_node	*node;
	int			size;

	size = 0;
	node = head;
	while (node)
	{
		size++;
		node = node->next_pipe;
	}
	return (size);
}

void	redirect_file(t_redirect_node *redirect)
{
	int	fd;

	if (redirect->type == T_INPUT)
		redirect_input(redirect->file_name, redirect->type);
	if (redirect->type == T_OUTPUT)
		redirect_output(redirect->file_name);
	if (redirect->type == T_HEREDOC)
		redirect_input(redirect->file_name, redirect->type);
	if (redirect->type == T_APPEND)
		redirect_append(redirect->file_name);
	if (redirect->left)
		redirect_file(redirect->left);
	if (redirect->right)
		redirect_file(redirect->right);
}

int	run_builtin_cmds(char *bin_name)
{
	const char	*builtins[7] = \
		{"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	int			idx;

	idx = 0;
	while (idx < 7)
	{
		if (ft_strncmp(builtins[idx], bin_name, ft_strlen(bin_name) + 1) == 0)
			break;
		idx++;
	}
	// builtin cmd has to be run
	if (idx == 7)
		return (0);
	return (1);
}

char	*get_bin_path(char	*bin_name)
{
	char	*bin_path;
	char	*path_env;
	char	**path_list;
	char	*tmp;

	path_env = getenv("PATH");
	if (run_builtin_cmds(bin_name))
		return (NULL);
	if (!path_env)
	path_list = ft_split(path_env, ':');
	if (!path_list)
		exit(EXIT_FAILURE); // malloc error
}

void	execute_simple_cmd(t_simple_cmd_node *simple_cmd)
{
	char	*bin_path;

	if (!simple_cmd || !simple_cmd->argv)
	{
		execve("/bin/cat", NULL, NULL);
		return ;
	}
	bin_path = get_bin_path(simple_cmd->argv[0]);
	// execve(bin_path, simple_cmd->argv, simple_cmd->envp);
}

void	execute_child(t_cmd_node *cmd, int	*pipe_fd)
{
	if (!cmd)
		return ;
	if (pipe_fd[0] >= 0 && pipe_fd[1] >= 0)
	{
		close(pipe_fd[0]);
		if (dup2(pipe_fd[1], STDOUT_FILENO) < 0)
			exit(EXIT_FAILURE); // dup2 error
		close(pipe_fd[1]);
	}
	if (cmd->redirect)
		redirect_file(cmd->redirect);
	execute_simple_cmd(cmd->simple_cmd);
}

void	heredoc_sub_preprocess(t_redirect_node *redirect, int *cnt)
{
	if (!redirect)
		return ;
	if (redirect->type == T_HEREDOC)
	{
		redirect_heredoc(&redirect->file_name, *cnt);
		(*cnt)++;
	}
	if (redirect->left)
		heredoc_sub_preprocess(redirect->left, cnt);
	if (redirect->right)
		heredoc_sub_preprocess(redirect->right, cnt);
}

void	heredoc_preprocess(t_pipe_node *head, int *cnt)
{
	if (head->cmd)
		heredoc_sub_preprocess(head->cmd->redirect, cnt);
	if (head->next_pipe)
		heredoc_preprocess(head->next_pipe, cnt);
}

void	unlink_tmpfile(int cnt)
{
	char	*str_num;
	char	*file_name;
	int		idx;

	idx = 0;
	while (idx < cnt)
	{
		str_num = ft_itoa(idx);
		file_name = ft_strjoin(".heredoc", str_num);
		unlink(file_name);
		free(str_num);
		free(file_name);
		idx++;
	}
}

int	execute_main(t_pipe_node *head)
{
	t_pipe_node	*pipe_node;
	int			pipe_size;
	t_pstat		*pstat;
	int			pipe_fd[2];
	int			idx;
	int			tmpfile_cnt;

	signal(SIGINT, sig_fork_handler);
	signal(SIGQUIT, sig_fork_handler);
	pipe_node = head;
	pipe_size = get_pipe_size(head);
	tmpfile_cnt = 0;
	heredoc_preprocess(head, &tmpfile_cnt);
	pstat = (t_pstat *)malloc(sizeof(t_pstat) * pipe_size);
	if (!pstat)
		exit_malloc_error();
	idx = 0;
	while (pipe_node)
	{
		if (pipe_node->next_pipe)
		{
			if (pipe(pipe_fd) < 0)
				exit(EXIT_FAILURE); // pipe error
		}
		else
		{
			pipe_fd[0] = -1;
			pipe_fd[1] = -1;
		}
		pstat[idx].pid = fork();
		if (pstat[idx].pid == 0)
			execute_child(pipe_node->cmd, pipe_fd);
		if (pipe_node->next_pipe)
		{
			close(pipe_fd[1]);
			if (dup2(pipe_fd[0], STDIN_FILENO) < 0)
				exit(EXIT_FAILURE); // dup2 error
			close(pipe_fd[0]);
		}
		pipe_node = pipe_node->next_pipe;
		idx++;
	}
	idx = 0;
	while (idx < pipe_size)
	{
		waitpid(pstat[idx].pid, &pstat[idx].exit_stat, 0);
		idx++;
	}
	unlink_tmpfile(tmpfile_cnt);
	free(pstat);
	return (1);
}

t_redirect_node	*create_redirect_node(char *filename, int type)
{
	t_redirect_node	*node;

	node = (t_redirect_node *)malloc(sizeof(t_redirect_node));
	node->left = NULL;
	node->right = NULL;
	node->file_name = filename;
	node->type = type;
	return (node);
}

int	main()
{
	t_pipe_node *head;

	head = (t_pipe_node *)malloc(sizeof(t_pipe_node));
	head->cmd = (t_cmd_node *)malloc(sizeof(t_cmd_node));
	head->cmd->simple_cmd = NULL;
	head->cmd->redirect = NULL;
	// head->cmd->redirect = create_redirect_node("EOF1", T_HEREDOC);
	// head->cmd->redirect->left = create_redirect_node("EOF2", T_HEREDOC);
	// head->cmd->redirect->right = create_redirect_node("outfile1", T_OUTPUT);

	head->next_pipe = (t_pipe_node *)malloc(sizeof(t_pipe_node));
	head->next_pipe->cmd = (t_cmd_node *)malloc(sizeof(t_cmd_node));
	head->next_pipe->cmd->simple_cmd = NULL;
	head->next_pipe->cmd->redirect = NULL;
	// head->next_pipe->cmd->redirect = create_redirect_node("EOF1", T_HEREDOC);
	// head->next_pipe->cmd->redirect->left = create_redirect_node("EOF2", T_HEREDOC);
	// head->next_pipe->cmd->redirect = create_redirect_node("outfile2", T_APPEND);
	head->next_pipe->next_pipe = NULL;
	execute_main(head);
	exit(EXIT_SUCCESS);
}

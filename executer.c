/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 15:37:17 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/04 16:49:27 by minjacho         ###   ########.fr       */
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
		if (!buf || ft_strncmp(buf, *deli, ft_strlen(*deli) + 1) == 0)
			break;
		else
		{
			write(fd, buf, ft_strlen(buf));
			write(fd, "\n", 1);
			free(buf);
		}
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

int	get_proc_cnt(t_pipe_node *head)
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

void	*get_builtin_func(char *func)
{
	if (ft_strcmp(func, "echo") == 0)
		return (ft_echo);
	if (ft_strcmp(func, "cd") == 0)
		return (ft_cd);
	if (ft_strcmp(func, "pwd") == 0)
		return (ft_pwd);
	if (ft_strcmp(func, "export") == 0)
		return (ft_export);
	if (ft_strcmp(func, "unset") == 0)
		return (ft_unset);
	if (ft_strcmp(func, "env") == 0)
		return (ft_env);
	if (ft_strcmp(func, "exit") == 0)
		return (ft_exit);
	return (NULL);
}

int	is_builtin_cmd(t_cmd_node *cmd)
{
	if (!cmd)
		return (0);
	if (!cmd->simple_cmd)
		return (0);
	if (!cmd->simple_cmd->argv)
		return (0);
	if (ft_strcmp(cmd->simple_cmd->argv[0], "echo") == 0)
		return (1);
	if (ft_strcmp(cmd->simple_cmd->argv[0], "cd") == 0)
		return (1);
	if (ft_strcmp(cmd->simple_cmd->argv[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd->simple_cmd->argv[0], "export") == 0)
		return (1);
	if (ft_strcmp(cmd->simple_cmd->argv[0], "unset") == 0)
		return (1);
	if (ft_strcmp(cmd->simple_cmd->argv[0], "env") == 0)
		return (1);
	if (ft_strcmp(cmd->simple_cmd->argv[0], "exit") == 0)
		return (1);
	return (0);
}

int	run_builtin_cmds(char **argv, t_dict **env_dict)
{
	int	idx;
	int	(*builtin_func)(char **, t_dict **);
	int	return_val;

	idx = 0;
	builtin_func = get_builtin_func(argv[0]);
	if (!builtin_func)
		return (-1);
	return_val = builtin_func(argv, env_dict);
	return (return_val);
}

char	**get_bin_path_list(char *path)
{
	char	**path_list;
	int		idx;
	char	*tmp;

	idx = 0;
	path_list = ft_split(path, ':');
	if (!path_list)
		exit(EXIT_FAILURE); // malloc error
	while (path_list[idx])
	{
		tmp = path_list[idx];
		path_list[idx] = ft_strjoin(tmp, "/");
		if (!path_list[idx])
			exit(EXIT_FAILURE);
		free(tmp);
		idx++;
	}
	return (path_list);
}

char	*get_bin_path(char	*bin_name, t_dict **env_dict)
{
	char	*bin_path;
	t_dict	*path_node;
	char	**path_list;
	int		idx;

	path_node = get_node_with_key(*env_dict, "PATH");
	if (!path_node || !path_node->value)
		return (NULL);
	path_list = get_bin_path_list(path_node->value);
	if (!path_list)
		exit(EXIT_FAILURE); // malloc error
	idx = 0;
	while (path_list[idx])
	{
		bin_path = ft_strjoin(path_list[idx], bin_name);
		if (!bin_path)
			exit(EXIT_FAILURE);
		if (access(bin_path, X_OK) == 0)
			break;
		free(bin_path);
		bin_path = NULL;
		idx++;
	}
	free_double_ptr(path_list);
	return (bin_path);
}

void	execute_simple_cmd(t_simple_cmd_node *simple_cmd, t_dict **env_dict)
{
	char	*bin_path;
	char	**envp;
	int		exit_code;

	if (!simple_cmd || !simple_cmd->argv)
		exit(EXIT_FAILURE); // command not found
	exit_code = run_builtin_cmds(simple_cmd->argv, env_dict);
	if (exit_code >= 0)
		exit(exit_code);
	if (ft_strncmp(simple_cmd->argv[0], "./", 2) == 0 ||
			ft_strncmp(simple_cmd->argv[0], "../", 3) == 0 ||
				ft_strncmp(simple_cmd->argv[0], "/", 1) == 0)
	{
		if (access(simple_cmd->argv[0], X_OK) == 0)
			exit(EXIT_FAILURE); // no such file or directory
	}
	else
	{
		bin_path = get_bin_path(simple_cmd->argv[0], env_dict);
		if (!bin_path)
			exit(EXIT_FAILURE); // command not found
	}
	envp = generate_envp(*env_dict);
	execve(bin_path, simple_cmd->argv, envp);
}

void	execute_child(t_cmd_node *cmd, int	*pipe_fd, t_dict **env_dict)
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
	execute_simple_cmd(cmd->simple_cmd, env_dict);
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

int	execute_main(t_pipe_node *head, t_dict **env_dict)
{
	t_pipe_node	*pipe_node;
	int			proc_cnt;
	t_pstat		*pstat;
	int			pipe_fd[2];
	int			idx;
	int			tmpfile_cnt;
	int			exit_stat;

	signal(SIGINT, sig_fork_handler);
	signal(SIGQUIT, sig_fork_handler);
	pipe_node = head;
	proc_cnt = get_proc_cnt(head);
	tmpfile_cnt = 0;
	heredoc_preprocess(head, &tmpfile_cnt);
	if (proc_cnt == 1 && is_builtin_cmd(head->cmd))
	{
		return (run_builtin_cmds(head->cmd->simple_cmd->argv, env_dict));
	}
	pstat = (t_pstat *)malloc(sizeof(t_pstat) * proc_cnt);
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
			execute_child(pipe_node->cmd, pipe_fd, env_dict);
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
	while (idx < proc_cnt)
	{
		waitpid(pstat[idx].pid, &pstat[idx].exit_stat, 0);
		idx++;
	}
	unlink_tmpfile(tmpfile_cnt);
	exit_stat = pstat[idx - 1].exit_stat;
	free(pstat);
	return (exit_stat);
}

t_redirect_node	*create_redirect_node(char *filename, int type)
{
	t_redirect_node	*node;

	node = (t_redirect_node *)malloc(sizeof(t_redirect_node));
	if (!node)
		exit(EXIT_FAILURE);
	node->left = NULL;
	node->right = NULL;
	node->file_name = filename;
	node->type = type;
	return (node);
}

void	f(void)
{
	system("leaks a.out");
}

int	main(int argc, char *argv[], char **envp)
{
	t_pipe_node *head;
	t_dict	*env_dict;
	int		exit_status;
	int		idx;

	atexit(f);
	env_dict = dict_init(envp);
	head = (t_pipe_node *)malloc(sizeof(t_pipe_node));
	head->cmd = (t_cmd_node *)malloc(sizeof(t_cmd_node));
	head->cmd->simple_cmd = (t_simple_cmd_node *)malloc(sizeof(t_simple_cmd_node));
	head->cmd->redirect = NULL;
	head->next_pipe = NULL;
	idx = 1;
	while (idx < argc)
	{
		head->cmd->simple_cmd->argv = ft_split(argv[idx], ' ');
		exit_status = execute_main(head, &env_dict);
		free_double_ptr(head->cmd->simple_cmd->argv);
		idx++;
	}
	exit(WEXITSTATUS(exit_status));
}
/*
int	main(int argc, char *argv[], char **envp)
{
	t_pipe_node *head;
	t_dict	*env_dict;
	int		exit_status;

	// atexit(f);
	env_dict = dict_init(envp);
	head = (t_pipe_node *)malloc(sizeof(t_pipe_node));
	head->cmd = (t_cmd_node *)malloc(sizeof(t_cmd_node));
	head->cmd->simple_cmd = (t_simple_cmd_node *)malloc(sizeof(t_simple_cmd_node));
	head->cmd->simple_cmd->argv = ft_split(argv[1], ' ');
	head->cmd->redirect = NULL;
	// head->cmd->redirect = create_redirect_node("EOF1", T_HEREDOC);
	head->cmd->redirect = create_redirect_node("/dev/urandom", T_INPUT);
	// head->cmd->redirect->left = create_redirect_node("EOF2", T_HEREDOC);
	// head->cmd->redirect->right = create_redirect_node("outfile1", T_OUTPUT);
	head->next_pipe = (t_pipe_node *)malloc(sizeof(t_pipe_node));
	head->next_pipe->cmd = (t_cmd_node *)malloc(sizeof(t_cmd_node));
	head->next_pipe->cmd->simple_cmd = NULL;
	head->next_pipe->cmd->simple_cmd = (t_simple_cmd_node *)malloc(sizeof(t_simple_cmd_node));
	head->next_pipe->cmd->simple_cmd->argv = ft_split(argv[2], ' ');
	head->next_pipe->cmd->redirect = NULL;
	// head->next_pipe->cmd->redirect = create_redirect_node("EOF1", T_HEREDOC);
	// head->next_pipe->cmd->redirect->left = create_redirect_node("EOF2", T_HEREDOC);
	head->next_pipe->cmd->redirect = create_redirect_node("outfile2", T_OUTPUT);
	head->next_pipe->next_pipe = NULL;
	exit_status = execute_main(head, &env_dict);
	exit(WEXITSTATUS(exit_status));
}
*/

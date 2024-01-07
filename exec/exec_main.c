/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 15:37:17 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/07 19:02:10 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_simple_cmd(t_cmd_node *cmd, t_dict **env_dict)
{
	char	*bin_path;
	char	**envp;
	int		exit_code;

	if (!cmd->argv || !cmd->argv[0])
		exit(EXIT_SUCCESS);
	exit_code = run_builtin(cmd, env_dict, 0, NULL);
	if (exit_code >= 0)
		exit(exit_code);
	if (ft_strncmp(cmd->argv[0], "./", 2) == 0
		|| ft_strncmp(cmd->argv[0], "../", 3) == 0
		|| ft_strncmp(cmd->argv[0], "/", 1) == 0)
	{
		if (access(cmd->argv[0], X_OK) != 0)
			exit_custom_err(NULL, cmd->argv[0], "No such file or directory", 1);
		bin_path = cmd->argv[0];
	}
	else
	{
		bin_path = get_bin_path(cmd->argv[0], env_dict);
		if (!bin_path)
			exit_custom_err(NULL, cmd->argv[0], "command not found", 127);
	}
	envp = generate_envp(*env_dict);
	execve(bin_path, cmd->argv, envp);
}

void	execute_child(t_cmd_node *cmd, int *pipe_fd, t_dict **env_dict)
{
	if (!cmd)
		return ;
	if (pipe_fd[0] >= 0 && pipe_fd[1] >= 0)
	{
		close(pipe_fd[0]);
		if (dup2(pipe_fd[1], STDOUT_FILENO) < 0)
			exit_custom_err(NULL, NULL, "Duplicate file error", 1);
		close(pipe_fd[1]);
	}
	if (cmd->redirect)
		redirect_file(cmd->redirect, 0);
	execute_simple_cmd(cmd, env_dict);
}

void	execute_pipe(t_pipe_node *head, t_dict **env_dict, t_pstat *pstat)
{
	t_pipe_node	*pipe_node;
	int			idx;
	int			pipe_fd[2];

	pipe_node = head;
	idx = 0;
	while (pipe_node)
	{
		init_pipe(pipe_fd, pipe_node->next_pipe);
		pstat[idx].pid = fork();
		if (pstat[idx].pid == 0)
			execute_child(pipe_node->cmd, pipe_fd, env_dict);
		if (pipe_node->next_pipe)
		{
			close(pipe_fd[1]);
			if (dup2(pipe_fd[0], STDIN_FILENO) < 0)
				exit_custom_err(NULL, NULL, "Duplicate file error", 1);
			close(pipe_fd[0]);
		}
		pipe_node = pipe_node->next_pipe;
		idx++;
	}
}

int	exit_by_child_state(t_pstat *pstat, int proc_cnt, int cnt, char *start_dir)
{
	int	idx;
	int	exit_stat;

	idx = 0;
	while (idx < proc_cnt)
	{
		waitpid(pstat[idx].pid, &pstat[idx].exit_stat, 0);
		idx++;
	}
	exit_stat = pstat[idx - 1].exit_stat;
	free(pstat);
	unlink_tmpfile(cnt, start_dir);
	return (WEXITSTATUS(exit_stat));
}

int	execute_main(t_pipe_node *head, t_dict **env_dict)
{
	int			proc_cnt;
	t_pstat		*pstat;
	int			tmpfile_cnt;
	int			origin_stdin;
	char		*start_dir;

	signal(SIGINT, sig_fork_handler);
	signal(SIGQUIT, sig_fork_handler);
	proc_cnt = get_proc_cnt(head);
	tmpfile_cnt = 0;
	start_dir = NULL;
	start_dir = getcwd(start_dir, 0);
	if (!start_dir)
		exit_custom_err(NULL, NULL, "Malloc error", 1);
	heredoc_preprocess(head, &tmpfile_cnt, start_dir);
	if (proc_cnt == 1 && is_builtin_cmd(head->cmd))
		return (run_builtin(head->cmd, env_dict, tmpfile_cnt, start_dir));
	pstat = (t_pstat *)malloc(sizeof(t_pstat) * proc_cnt);
	if (!pstat)
		exit_custom_err(NULL, NULL, "Malloc error", 1);
	origin_stdin = dup(STDIN_FILENO);
	execute_pipe(head, env_dict, pstat);
	dup2(origin_stdin, STDIN_FILENO);
	close(origin_stdin);
	return (exit_by_child_state(pstat, proc_cnt, tmpfile_cnt, start_dir));
}

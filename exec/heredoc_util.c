/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:07:21 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/10 13:21:09 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_heredoc_fork(t_pipe_node *head, int *cnt, char *start_dir)
{
	pid_t	pid;
	int		exit_state;

	turn_off_ctrl();
	pid = fork();
	signal(SIGINT, sig_heredoc_handler);
	signal(SIGQUIT, sig_heredoc_handler);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		heredoc_preprocess(head, cnt, start_dir, 1);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &exit_state, 0);
		heredoc_preprocess(head, cnt, start_dir, 0);
		turn_on_ctrl();
		if (WIFSIGNALED(exit_state))
			unlink_tmpfile(get_heredoc_file_cnt(head), start_dir);
	}
	return (exit_state);
}

int	get_heredoc_file_cnt_sub(t_redir_node *redir)
{
	int	cnt;

	cnt = 0;
	if (!redir)
		return (0);
	if (redir->type == E_TYPE_REDIR_HEREDOC)
		cnt++;
	if (redir->next)
		cnt += get_heredoc_file_cnt_sub(redir->next);
	return (cnt);
}

int	get_heredoc_file_cnt(t_pipe_node *head)
{
	int	cnt;

	cnt = 0;
	if (head->cmd)
		cnt += get_heredoc_file_cnt_sub(head->cmd->redirect);
	if (head->next_pipe)
		cnt += get_heredoc_file_cnt(head->next_pipe);
	return (cnt);
}

void	unlink_tmpfile(int cnt, char *start_dir)
{
	char	*str_num;
	char	*file_name;
	int		idx;
	char	*heredoc_prefix;

	heredoc_prefix = ft_strjoin(start_dir, "/.heredoc-");
	if (!heredoc_prefix)
		exit_custom_err(NULL, NULL, "Malloc error", 1);
	idx = 0;
	while (idx < cnt)
	{
		str_num = ft_itoa(idx);
		if (!str_num)
			exit_custom_err(NULL, NULL, "Malloc error", 1);
		file_name = ft_strjoin(heredoc_prefix, str_num);
		if (!file_name)
			exit_custom_err(NULL, NULL, "Malloc error", 1);
		unlink(file_name);
		free(str_num);
		free(file_name);
		idx++;
	}
	free(heredoc_prefix);
	free(start_dir);
}

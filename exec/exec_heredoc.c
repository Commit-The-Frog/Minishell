/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 19:04:20 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/07 15:48:18 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_sub_preprocess(t_redir_node *redir, int *cnt, char *start_dir)
{
	if (!redir)
		return ;
	if (redir->type == E_TYPE_REDIR_HEREDOC)
	{
		redirect_heredoc(&redir->file_name, *cnt, start_dir);
		(*cnt)++;
	}
	if (redir->next)
		heredoc_sub_preprocess(redir->next, cnt, start_dir);
}

void	heredoc_preprocess(t_pipe_node *head, int *cnt, char *start_dir)
{
	if (head->cmd)
		heredoc_sub_preprocess(head->cmd->redirect, cnt, start_dir);
	if (head->next_pipe)
		heredoc_preprocess(head->next_pipe, cnt, start_dir);
}

static void	heredoc_file(int fd, char **deli)
{
	char	*buf;

	while (1)
	{
		buf = readline("> ");
		if (!buf || ft_strncmp(buf, *deli, ft_strlen(*deli) + 1) == 0)
			break ;
		else
		{
			write(fd, buf, ft_strlen(buf));
			write(fd, "\n", 1);
			free(buf);
		}
	}
	free(buf);
}

void	redirect_heredoc(char **deli, int cnt, char *start_dir)
{
	char	*tmp_file;
	char	*str_cnt;
	int		fd;
	char	*heredoc_prefix;

	heredoc_prefix = ft_strjoin(start_dir, "/.heredoc-");
	if (!heredoc_prefix)
		exit_custom_err(NULL, NULL, "Malloc error", 1);
	str_cnt = ft_itoa(cnt);
	if (!str_cnt)
		exit_custom_err(NULL, NULL, "Malloc error", 1);
	tmp_file = ft_strjoin(heredoc_prefix, str_cnt);
	if (!tmp_file)
		exit_custom_err(NULL, NULL, "Malloc error", 1);
	free(str_cnt);
	free(heredoc_prefix);
	fd = open(tmp_file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		exit_custom_err(NULL, tmp_file, "File open error", 1);
	heredoc_file(fd, deli);
	free(*deli);
	*deli = tmp_file;
	close(fd);
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
}

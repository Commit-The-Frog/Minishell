/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 19:04:20 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/10 13:21:58 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_sub_preprocess(\
	t_redir_node *redir, int *cnt, char *start_dir, int get_input)
{
	if (!redir)
		return ;
	if (redir->type == E_TYPE_REDIR_HEREDOC)
	{
		redirect_heredoc(&redir->file_name, *cnt, start_dir, get_input);
		(*cnt)++;
	}
	if (redir->next)
		heredoc_sub_preprocess(redir->next, cnt, start_dir, get_input);
}

void	heredoc_preprocess(\
	t_pipe_node *head, int *cnt, char *start_dir, int get_input)
{
	if (head->cmd)
		heredoc_sub_preprocess(head->cmd->redirect, cnt, start_dir, get_input);
	if (head->next_pipe)
		heredoc_preprocess(head->next_pipe, cnt, start_dir, get_input);
}

static void	heredoc_file(char *tmp_file, char **deli)
{
	int		fd;
	char	*buf;

	fd = open(tmp_file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		exit_custom_err(NULL, tmp_file, "File open error", 1);
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
	close(fd);
}

void	redirect_heredoc(char **deli, int cnt, char *start_dir, int get_input)
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
	if (get_input)
		heredoc_file(tmp_file, deli);
	free(*deli);
	*deli = tmp_file;
}

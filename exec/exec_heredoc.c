/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 19:04:20 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/06 19:12:06 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_exec.h"

void	heredoc_sub_preprocess(t_redir_node *redirect, int *cnt)
{
	if (!redirect)
		return ;
	if (redirect->type == E_TYPE_REDIR_HEREDOC)
	{
		redirect_heredoc(&redirect->file_name, *cnt);
		(*cnt)++;
	}
	if (redirect->next)
		heredoc_sub_preprocess(redirect->next, cnt);
}

void	heredoc_preprocess(t_pipe_node *head, int *cnt)
{
	if (head->cmd)
		heredoc_sub_preprocess(head->cmd->redirect, cnt);
	if (head->next_pipe)
		heredoc_preprocess(head->next_pipe, cnt);
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

void	redirect_heredoc(char **deli, int cnt)
{
	char	*tmp_file;
	char	*str_cnt;
	int		fd;

	str_cnt = ft_itoa(cnt);
	if (!str_cnt)
		exit_custom_err(NULL, NULL, "Malloc error", 1);
	tmp_file = ft_strjoin(".heredoc_dir/", str_cnt);
	if (!tmp_file)
		exit_custom_err(NULL, NULL, "Malloc error", 1);
	free(str_cnt);
	fd = open(tmp_file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		exit_custom_err(NULL, tmp_file, "File open error", 1);
	heredoc_file(fd, deli);
	*deli = tmp_file;
	close(fd);
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
		file_name = ft_strjoin(".heredoc_dir/", str_num);
		unlink(file_name);
		free(str_num);
		free(file_name);
		idx++;
	}
}

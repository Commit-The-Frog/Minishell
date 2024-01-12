/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 19:04:20 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/11 17:27:54 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	trim_quote(char **deli)
{
	char	set[2];
	char	*new_str;

	set[0] = is_quote(*deli, 0);
	set[1] = 0;
	if (set[0])
	{
		new_str = ft_strtrim(*deli, set);
		if (!new_str)
			exit_custom_err(NULL, NULL, "Malloc error", 1);
		free(*deli);
		*deli = new_str;
		return (1);
	}
	return (0);
}

static void	expand_buf(char **buf, t_dict *dict)
{
	char	*tmp;

	tmp = heredoc_expand_str(*buf, dict);
	free(*buf);
	*buf = tmp;
}

static void	heredoc_file(char *tmp_file, char **deli, t_dict **dict)
{
	int		fd;
	char	*buf;
	int		deli_has_quote;

	fd = open(tmp_file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		exit_custom_err(NULL, tmp_file, "File open error", 1);
	deli_has_quote = trim_quote(deli);
	while (1)
	{
		buf = readline("> ");
		if (!buf || ft_strncmp(buf, *deli, ft_strlen(*deli) + 1) == 0)
			break ;
		else
		{
			if (!deli_has_quote && ft_strchr(buf, '$'))
				expand_buf(&buf, *dict);
			write(fd, buf, ft_strlen(buf));
			write(fd, "\n", 1);
			free(buf);
		}
	}
	free(buf);
	close(fd);
}

void	redirect_heredoc(char **deli, \
			char *start_dir, int get_input, t_dict **dict)
{
	static int	cnt = 0;
	char		*tmp_file;
	char		*str_cnt;
	char		*heredoc_prefix;

	if (get_input == 2)
		return (unlink_tmpfile(cnt, start_dir));
	heredoc_prefix = ft_strjoin(start_dir, "/.heredoc-");
	if (!heredoc_prefix)
		exit_custom_err(NULL, NULL, "Malloc error", 1);
	str_cnt = ft_itoa(cnt);
	cnt++;
	if (!str_cnt)
		exit_custom_err(NULL, NULL, "Malloc error", 1);
	tmp_file = ft_strjoin(heredoc_prefix, str_cnt);
	if (!tmp_file)
		exit_custom_err(NULL, NULL, "Malloc error", 1);
	free(str_cnt);
	free(heredoc_prefix);
	if (get_input)
		heredoc_file(tmp_file, deli, dict);
	free(*deli);
	*deli = tmp_file;
}

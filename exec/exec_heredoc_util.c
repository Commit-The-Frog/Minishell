/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 21:07:27 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/10 21:08:01 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_sub_preprocess(\
	t_redir_node *redir, char *start_dir, int get_input, t_dict **dict)
{
	if (!redir)
		return ;
	if (redir->type == E_TYPE_REDIR_HEREDOC)
		redirect_heredoc(&redir->file_name, start_dir, get_input, dict);
	if (redir->next)
		heredoc_sub_preprocess(redir->next, start_dir, get_input, dict);
}

void	heredoc_preprocess(\
	t_pipe_node *head, char *start_dir, int get_input, t_dict **dict)
{
	if (head->cmd)
		heredoc_sub_preprocess(head->cmd->redirect, start_dir, get_input, dict);
	if (head->next_pipe)
		heredoc_preprocess(head->next_pipe, start_dir, get_input, dict);
}

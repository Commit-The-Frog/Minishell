/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 20:31:52 by junkim2           #+#    #+#             */
/*   Updated: 2024/01/05 22:35:20 by junkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_redir_node(t_redir_node **redir, t_token **cur)
{
	t_redir_node	*new;
	t_redir_node	*cur_redir;
	t_token			*tmp;

	new = (t_redir_node *)ft_calloc(1, sizeof(t_redir_node));
	if (new == NULL)
		exit (EXIT_FAILURE);
	new->type = (*cur)->type;
	*cur = (*cur)->next;
	new->file_name = ft_strdup((*cur)->str);
	if (new->file_name == NULL)
		exit(EXIT_FAILURE);
	cur_redir = *redir;
	if (cur_redir == NULL)
		*redir = new;
	else
	{
		while (cur_redir->next)
			cur_redir = cur_redir->next;
		cur_redir->next = new;
	}
	*cur = (*cur)->next;
}

t_cmd_node	*get_cmd_node(t_pipe_node *pipe, t_token **cur)
{
	t_cmd_node	*cmd;

	cmd = (t_cmd_node *)ft_calloc(1, sizeof(t_cmd_node));
	if (cmd == NULL)
		exit(EXIT_FAILURE);
	cmd->redirect = NULL;
	cmd->simple_cmd = NULL;
	while (*cur && (*cur)->type != E_TYPE_PIPE)
	{
		if ((*cur)->type >= 5 && (*cur)->type <= 9)
			get_redir_node(&(cmd->redirect), cur);
	}
	return (cmd);
}

void	get_pipe_node(t_pipe_node **ast, t_token **token_list)
{
	t_pipe_node	*pipe;

	pipe = (t_pipe_node *)ft_calloc(1, sizeof(t_pipe_node));
	if (pipe == NULL)
		exit(EXIT_FAILURE);
	pipe->cmd = get_cmd_node(pipe, token_list);
	*ast = pipe;
}

void	get_ast(t_pipe_node **ast, t_token **token_list)
{
	t_pipe_node		*cur;
	t_cmd_node		*cur_cmd;
	t_redir_node	*cur_redir;

	get_pipe_node(ast, token_list);
	cur = *ast;
	while (cur)
	{
		cur_cmd = cur->cmd;
		cur_redir = cur_cmd->redirect;
		while (cur_redir)
		{
			printf("%u, %s\n", (unsigned int)cur_redir->type, cur_redir->file_name);
			cur_redir = cur_redir->next;
		}
		cur = cur->next_pipe;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 20:31:52 by junkim2           #+#    #+#             */
/*   Updated: 2024/01/07 17:39:24 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_simple_cmd_node(t_simple_cmd_node **simple_cmd, t_token **cur)
{
	t_simple_cmd_node	*new;
	t_simple_cmd_node	*cur_simple_cmd;

	new = (t_simple_cmd_node *)ft_calloc(1, sizeof(t_simple_cmd_node));
	if (new == NULL)
		exit(EXIT_FAILURE);
	new->is_expand = 0;
	if ((*cur)->type == E_TYPE_EXPAND)
		new->is_expand = 1;
	new->argv = ft_strdup((*cur)->str);
	if (new->argv == NULL)
		exit(EXIT_FAILURE);
	// printf("simple cmd: %s\n", new->argv);
	new->next = NULL;
	if (*simple_cmd == NULL)
	{
		*simple_cmd = new;
		return ;
	}
	cur_simple_cmd = *simple_cmd;
	while (cur_simple_cmd->next)
		cur_simple_cmd = cur_simple_cmd->next;
	cur_simple_cmd->next = new;
}

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
	if (*cur == NULL)
		return ;
	if ((*cur)->type >= 5 && (*cur)->type <= 8)
	{
		syntax_err((*cur)->str);
		return ;
	}
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
}

void	get_argv_array(t_simple_cmd_node *list, char **arr)
{
	t_simple_cmd_node	*cur;
	char				**tmp_arr;
	int					i;
	int					j;

	cur = list;
	i = 0;
	while (cur)
	{
		if (cur->is_expand == 1)
		{
			tmp_arr = ft_split(cur->argv, ' ');
			j = 0;
			while (tmp_arr[j])
			{
				arr[i++] = ft_strdup(tmp_arr[j]);
				free(tmp_arr[j]);
				j++;
			}
			free(tmp_arr);
			tmp_arr = NULL;
		}
		else
			arr[i++] = ft_strdup(cur->argv);
		cur = cur->next;
	}
}

char	**conv_list_to_array(t_simple_cmd_node *list)
{
	t_simple_cmd_node	*cur;
	int					count;
	char				**arr;

	cur = list;
	count = 0;
	while (cur)
	{
		if (cur->is_expand == 1)
			count += count_word(cur->argv) + 1;
		else
			count++;
		cur = cur->next;
	}
	arr = (char **)ft_calloc(count + 1, sizeof(char *));
	if (arr == NULL)
		exit(EXIT_FAILURE);
	get_argv_array(list, arr);
	return (arr);
}

t_cmd_node	*get_cmd_node(t_pipe_node *pipe, t_token **cur)
{
	t_cmd_node			*cmd;

	cmd = (t_cmd_node *)ft_calloc(1, sizeof(t_cmd_node));
	if (cmd == NULL)
		exit(EXIT_FAILURE);
	cmd->redirect = NULL;
	cmd->simple_cmd = NULL;
	while (*cur && (*cur)->type != E_TYPE_PIPE)
	{
		if ((*cur)->type >= 5 && (*cur)->type <= 8)
			get_redir_node(&(cmd->redirect), cur);
		else if ((*cur)->type == E_TYPE_SIMPLE_CMD || (*cur)->type == E_TYPE_EXPAND)
			get_simple_cmd_node(&(cmd->simple_cmd), cur);
		if (*cur == NULL)
			break;
		*cur = (*cur)->next;
	}
	cmd->argv = conv_list_to_array(cmd->simple_cmd);
	return (cmd);
}

void	get_pipe_node(t_pipe_node **root, t_token **token_list)
{
	t_pipe_node	*pipe;

	pipe = (t_pipe_node *)ft_calloc(1, sizeof(t_pipe_node));
	if (pipe == NULL)
		exit(EXIT_FAILURE);
	pipe->cmd = get_cmd_node(pipe, token_list);
	if (*token_list && (*token_list)->type == E_TYPE_PIPE)
	{
		*token_list = (*token_list)->next;
		get_pipe_node(&pipe->next_pipe, token_list);
	}
	*root = pipe;
}

void	get_ast(t_pipe_node **ast, t_token **token_list)
{
	t_pipe_node			*cur;
	t_token				*cur_token;
	t_token				*tmp;
	t_cmd_node			*cur_cmd;
	t_redir_node		*cur_redir;
	t_simple_cmd_node	*cur_scmd;
	int					i;

	cur_token = *token_list;
	get_pipe_node(ast, token_list);
	// printing..
	// cur = *ast;
	// while (cur)
	// {
	// 	cur_cmd = cur->cmd;
	// 	cur_redir = cur_cmd->redirect;
	// 	cur_scmd = cur_cmd->simple_cmd;
	// 	printf("====redirects====\n");
	// 	while (cur_redir)
	// 	{
	// 		printf("%u, %s\n", (unsigned int)cur_redir->type, cur_redir->file_name);
	// 		cur_redir = cur_redir->next;
	// 	}
	// 	printf("====simple cmd====\n");
	// 	while (cur_scmd)
	// 	{
	// 		printf("[%s]", cur_scmd->argv);
	// 		cur_scmd = cur_scmd->next;
	// 	}
	// 	printf("\n====argv====\n");
	// 	i = 0;
	// 	while (cur_cmd->argv[i])
	// 	{
	// 		printf("[%s] ", cur_cmd->argv[i++]);
	// 	}
	// 	printf("\n");
	// 	cur = cur->next_pipe;
	// }

	// freeing tokenlist...
	while (cur_token)
	{
		tmp = cur_token;
		cur_token = cur_token->next;
		free(tmp);
		free(tmp->str);
	}
}

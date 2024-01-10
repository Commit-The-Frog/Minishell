/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_io.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 18:58:54 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/10 15:04:29 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_input(char *file_name, int is_builtin)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (is_builtin)
	{
		if (fd < 0)
			return (print_custom_err(NULL, file_name,
					"No such file or directory", 1));
		if (access(file_name, R_OK) < 0)
			return (print_custom_err(NULL, file_name, "Permission denied", 1));
		if (dup2(fd, STDIN_FILENO) < 0)
			return (print_custom_err(NULL, file_name,
					"Duplicate file error", 1));
		close(fd);
		return (0);
	}
	if (access(file_name, F_OK) < 0)
		exit_custom_err(NULL, file_name, "No such file or directory", 1);
	if (access(file_name, R_OK) < 0)
		exit_custom_err(NULL, file_name, "Permission denied", 1);
	if (dup2(fd, STDIN_FILENO) < 0)
		exit_custom_err(NULL, file_name, "Duplicate file error", 1);
	close(fd);
	return (0);
}

int	redirect_output(char *file_name, int is_builtin)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (is_builtin)
	{
		if (fd < 0)
			return (print_custom_err(NULL, file_name,
					"No such file or directory", 1));
		if (access(file_name, W_OK) < 0)
			return (print_custom_err(NULL, file_name, "Permission denied", 1));
		if (dup2(fd, STDOUT_FILENO) < 0)
			return (print_custom_err(NULL, file_name,
					"Duplicate file error", 1));
		close(fd);
		return (0);
	}
	if (access(file_name, F_OK) < 0)
		exit_custom_err(NULL, file_name, "No such file or directory", 1);
	if (access(file_name, W_OK) < 0)
		exit_custom_err(NULL, file_name, "Permission denied", 1);
	if (dup2(fd, STDOUT_FILENO) < 0)
		exit_custom_err(NULL, file_name, "Duplicate file error", 1);
	close(fd);
	return (0);
}

int	redirect_append(char *file_name, int is_builtin)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (is_builtin)
	{
		if (access(file_name, W_OK) < 0)
			return (print_custom_err(NULL, file_name, "Permission denied", 1));
		if (fd < 0)
			return (print_custom_err(NULL, file_name,
					"No such file or directory", 1));
		if (dup2(fd, STDOUT_FILENO) < 0)
			return (print_custom_err(NULL, file_name,
					"Duplicate file error", 1));
		close(fd);
		return (0);
	}
	if (access(file_name, F_OK) < 0)
		exit_custom_err(NULL, file_name, "No such file or directory", 1);
	if (access(file_name, W_OK) < 0)
		exit_custom_err(NULL, file_name, "Permission denied", 1);
	if (dup2(fd, STDOUT_FILENO) < 0)
		exit_custom_err(NULL, file_name, "Duplicate file error", 1);
	close(fd);
	return (0);
}

int	redirect_file(t_redir_node *redirect, int is_builtin)
{
	int	res;

	res = 0;
	if (!redirect)
		return (0);
	if (redirect->type == E_TYPE_REDIR_LEFT)
		res = redirect_input(redirect->file_name, is_builtin);
	if (redirect->type == E_TYPE_REDIR_RIGHT)
		res = redirect_output(redirect->file_name, is_builtin);
	if (redirect->type == E_TYPE_REDIR_HEREDOC)
		res = redirect_input(redirect->file_name, is_builtin);
	if (redirect->type == E_TYPE_REDIR_APPEND)
		res = redirect_append(redirect->file_name, is_builtin);
	if (res)
		return (res);
	if (redirect->next)
		res = redirect_file(redirect->next, is_builtin);
	return (res);
}

void	init_pipe(int *pipe_fd, t_pipe_node *next_pipe)
{
	if (next_pipe)
	{
		if (pipe(pipe_fd) < 0)
			exit_custom_err(NULL, NULL, "Pipe error", 1);
	}
	else
	{
		pipe_fd[0] = -1;
		pipe_fd[1] = -1;
	}
}

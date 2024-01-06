/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_io.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 18:58:54 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/06 20:34:58 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_input(char *file_name, int type)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (access(file_name, R_OK) < 0)
		exit_custom_err(NULL, file_name, "Permission denied", 1);
	if (fd < 0)
		exit_custom_err(NULL, file_name, "No such file or directory", 1);
	if (dup2(fd, STDIN_FILENO) < 0)
		exit_custom_err(NULL, file_name, "Duplicate file error", 1);
	close(fd);
	if (type == E_TYPE_REDIR_HEREDOC)
		free(file_name);
}

void	redirect_output(char *file_name)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (access(file_name, W_OK) < 0)
		exit_custom_err(NULL, file_name, "Permission denied", 1);
	if (fd < 0)
		exit_custom_err(NULL, file_name, "File create error", 1);
	if (dup2(fd, STDOUT_FILENO) < 0)
		exit_custom_err(NULL, file_name, "Duplicate file error", 1);
	close(fd);
}

void	redirect_append(char *file_name)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (access(file_name, W_OK) < 0)
		exit_custom_err(NULL, file_name, "Permission denied", 1);
	if (fd < 0)
		exit_custom_err(NULL, file_name, "No such file or directory", 1);
	if (dup2(fd, STDOUT_FILENO) < 0)
		exit_custom_err(NULL, file_name, "Duplicate file error", 1);
	close(fd);
}

void	redirect_file(t_redir_node *redirect)
{
	int	fd;

	if (redirect->type == E_TYPE_REDIR_LEFT)
		redirect_input(redirect->file_name, redirect->type);
	if (redirect->type == E_TYPE_REDIR_RIGHT)
		redirect_output(redirect->file_name);
	if (redirect->type == E_TYPE_REDIR_HEREDOC)
		redirect_input(redirect->file_name, redirect->type);
	if (redirect->type == E_TYPE_REDIR_APPEND)
		redirect_append(redirect->file_name);
	if (redirect->next)
		redirect_file(redirect->next);
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

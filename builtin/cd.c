/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:17:58 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/11 16:10:11 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_is_valid_dir(char *path)
{
	struct stat	stat_buf;

	if (access(path, F_OK) < 0)
		return (print_custom_err("cd", path, "No such file or directory", 1));
	if (stat(path, &stat_buf) < 0)
		return (print_custom_err("cd", path, "stat function error", 1));
	if (!S_ISDIR(stat_buf.st_mode))
		return (print_custom_err("cd", path, "Not a directory", 1));
	if (access(path, X_OK) < 0)
		return (print_custom_err("cd", path, "Permission denied", 1));
	return (0);
}

static char	*get_relative_path(char **argv, t_dict **env_dict)
{
	char	*old_pwd;
	char	*pwd;

	print_custom_err("cd", "getcwd", "error retrieving current directory", 1);
	old_pwd = get_value_with_key(*env_dict, "PWD");
	if (!old_pwd)
		return (NULL);
	old_pwd = ft_strjoin(old_pwd, "/");
	if (!old_pwd)
		exit_custom_err("NULL", "NULL", "Malloc error", 1);
	pwd = ft_strjoin(old_pwd, argv[1]);
	if (!pwd)
		exit_custom_err("NULL", "NULL", "Malloc error", 1);
	free(old_pwd);
	return (pwd);
}

static void	set_pwd_env(int argc, char **argv, t_dict **env_dict)
{
	char	*pwd;
	char	*env;

	if (argc == 1)
	{
		pwd = ft_strdup(get_value_with_key(*env_dict, "HOME"));
		if (!pwd)
			exit_custom_err("NULL", "NULL", "Malloc error", 1);
	}
	else
	{
		pwd = NULL;
		pwd = getcwd(pwd, 0);
		if (!pwd)
			pwd = get_relative_path(argv, env_dict);
	}
	if (!pwd)
		return ;
	env = ft_strjoin("PWD=", pwd);
	if (!env)
		exit_custom_err("NULL", "NULL", "Malloc error", 1);
	add_node_back(env_dict, env);
	free(env);
	free(pwd);
}

int	ft_cd(char **argv, t_dict **env_dict)
{
	int		argc;
	t_dict	*home_dict;

	argc = 0;
	while (argv && argv[argc])
		argc++;
	if (argc > 1)
	{
		if (check_is_valid_dir(argv[1]) != 0)
			return (1);
		if (chdir(argv[1]) < 0)
			return (print_custom_err("cd", argv[1], "chdir function error", 1));
	}
	else
	{
		home_dict = get_node_with_key(*env_dict, "HOME");
		if (!home_dict)
			return (print_custom_err("cd", NULL, "HOME not set", 1));
		if (check_is_valid_dir(home_dict->value) != 0)
			return (1);
		if (chdir(home_dict->value) < 0)
			return (print_custom_err("cd", argv[1], "chdir function error", 1));
	}
	set_pwd_env(argc, argv, env_dict);
	return (0);
}

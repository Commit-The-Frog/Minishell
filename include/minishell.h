/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 11:53:33 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/09 14:07:40 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEMO_MINISHELL_H
# define DEMO_MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <sys/errno.h>
# include "libft.h"
# include "mini_type.h"
# include "mini_exec.h"

void		sig_handler(int signo);
void		sig_fork_handler(int signo);
void		get_more_input(char **origin);
void		tokenize(t_token **list, char *str, t_dict *dict);
void    	print_logo(void);
void		sep_token(t_token **list, char *str);
void		make_token(t_token **list, char *str, int start, int end);
void		remove_quote(t_token **list);
char		is_operator(char c);
int			is_double_operator(char c1, char c2);
void		get_ast(t_pipe_node **ast, t_token **token_list);
t_pipe_node	*parse(char *str, t_dict *dict);
void		*quote_err(char c);
char		is_quote(char *str, int	idx);
void		expand_var(t_token **list, t_dict *dict);
void		*syntax_err(char *str);
void		remove_empty_token(t_token **token_list);
int			count_word(char *str);
void		restore_recent_exit(int recent_exit, t_dict **env_dict);
int			ft_sigismember(sigset_t *dst_set, int signo);
sigset_t	recent_sig;
void		insert_token(t_token **list, char *str, int start);
void		split_token(t_token **list);
void		expand_env(t_token *token, t_dict *env_dict);
//printer
void	token_list_printer(t_token *token_list);
void	turn_off_ctrl();
void	turn_on_ctrl();

int	get_heredoc_file_cnt(t_pipe_node *head);

#endif

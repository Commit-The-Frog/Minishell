/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 11:53:33 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/10 14:48:46 by junkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

sigset_t	recent_sig;

// ========= core.c =========
t_pipe_node	*parse(char *str, t_dict *dict);

// ========= quote.c =========
char		is_quote(char *str, int idx);
char		check_quote(char *str);

// ========= error.c =========
void		*quote_err(char c);
void		*syntax_err(char *str);

// ========= lexer.c =========
void		*make_token(t_token **list, char *str, int start, int end);
void		insert_token(t_token **list, char *str, int start);
void		tokenize(t_token **list, char *str, t_dict *dict);

// ========= tokenize.c =========
void		sep_token(t_token **list, char *str);
void		split_token(t_token **list);

void		sig_handler(int signo);
void		sig_fork_handler(int signo);
void		get_more_input(char **origin);
void		print_logo(void);
void		remove_quote(t_token **list);
char		is_operator(char c);
int			is_double_operator(char c1, char c2);
void		get_ast(t_pipe_node **ast, t_token **token_list);
void		expand_var(t_token **list, t_dict *dict);
void		remove_empty_token(t_token **token_list);
int			count_word(char *str);
void		restore_recent_exit(int recent_exit, t_dict **env_dict);
int			ft_sigismember(sigset_t *dst_set, int signo);
void		expand_env(t_token *token, t_dict *env_dict);
int			is_double_operator(char c1, char c2);
int			get_type(t_token *token);
//printer
void		token_list_printer(t_token *token_list);

#endif

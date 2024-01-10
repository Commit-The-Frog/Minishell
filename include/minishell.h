/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 11:53:33 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/10 22:20:37 by junkim2          ###   ########.fr       */
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

sigset_t	g_recent_sig;

// ========= core.c =========
int			parse(char *str, t_dict *dict, t_pipe_node **ast);

// ========= quote.c =========
char		is_quote(char *str, int idx);
char		check_quote(char *str);
void		remove_quote(t_token **list);

// ========= checker.c =========
int			check_ambiguous(t_token **list, char *str);
int			check_unexpected_token(t_token **list);

// ========= error.c =========
void		*quote_err(char c);
void		*syntax_err(char *str, int *err_flag);
void		*ambiguous_err(char *str);

// ========= lexer.c =========
void		*make_token(t_token **list, char *str, int start, int end);
void		insert_token(t_token **list, char *str, int start);
int			tokenize(t_token **list, char *str, t_dict *dict);

// ========= tokenize.c =========
void		sep_token(t_token **list, char *str);
void		split_token(t_token **list);

// ========= logo.c =========
void		print_logo(void);

// ========= expand_util.c =========
size_t		get_total_len(char *str, t_dict *env_dict);
size_t		get_var_len(char *str);
size_t		get_env_length(char *env_name, t_dict *env_dict);
char		set_quote_flag(char quote_flag, char *str, int idx);
void		remove_empty_token(t_token **token_list);

// ========= expand.c =========
void		expand_var(t_token **list, t_dict *dict);
void		expand_env(t_token *token, t_dict *env_dict);
void		set_expanded_str(char *str, char *result, \
							size_t size, t_dict *env_dict);

// ========= util.c =========
int			count_word(char *str);
char		is_operator(char c);
int			is_double_operator(char c1, char c2);
int			get_type(t_token *token);
char		*expand_str(char *origin, t_dict *env_dict);

// ========= parser.c =========
void		get_ast(t_pipe_node **ast, t_token **token_list);

// ========= parser_util.c =========
void		get_argv_array(t_simple_cmd_node *list, char **arr);
char		**conv_list_to_array(t_simple_cmd_node *list);

// ========= sighandler.c =========
void		sig_handler(int signo);
void		sig_fork_handler(int signo);
int			ft_sigismember(sigset_t *dst_set, int signo);

// ========= prompt.c =========
void		restore_recent_exit(int recent_exit, t_dict **env_dict);

// ========= prompt_util.c =========
void		turn_off_ctrl(void);
void		turn_on_ctrl(void);

//printer
void		token_list_printer(t_token *token_list);
void		ast_printer(t_pipe_node *ast);
void		fuck(void);

int			get_heredoc_file_cnt(t_pipe_node *head);
void		sig_heredoc_handler(int signo);
int			is_path(char *str);
int			process_heredoc_fork(t_pipe_node *head, char *start_dir, t_dict **dict);
void		sig_heredoc_handler(int signo);
void		switch_signal_handler(int forked);
void		free_ast(t_pipe_node **ast);
void		free_token_list(t_token **list);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   demo_minishell.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 11:53:33 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/01 20:48:24 by junkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEMO_MINISHELL_H
# define DEMO_MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
/*
	char	*readline(const char *);
	void	rl_clear_history(void);
	rl_on_new_line;
	rl_replace_line;
	rl_redisplay;
	add_history;
*/

# include <stdio.h>
/*
	printf, strerror, perror
*/

# include <stdlib.h>
/*
	malloc, free, exit, getenv
*/

# include <unistd.h>
/*
	write, access, read, close, fork

	char	*getcwd(char *buf, size_t size)
	// copies the absolute pathname of the current working directory into buf
	// 버퍼에 현재 작업 위치의 절대경로 저장.

	int	chdir(const char *path)
	// path에 해당하는 위치로 작업 디렉토리 변경. 실패하면 -1 성공하면 0
	// access 먼저 하고 해야될 듯?

	stat, lstat, fstat
	// 파일의 속성들에 대한 함수이다. path나 fd를 넘겨주면 해당 파일에 대한 정보를 stat *buf에 넣어준다.

	unlink, execve, dup, dup2, pipe

	isatty, ttyname, ttyslot
	// int	isatty(int fd) 해당 fd가 tty인지 확인해준다.
	// int	ttyname(int fd) fd에 대한 tty 이름을 알려줌.
	//
*/

# include <fcntl.h>
/*
	open
*/

# include <sys/wait.h>
/*
	wait, wait3, wait4, waitpid
*/

# include <signal.h>
/*
	signal, sigaction, sigemptyset, sigaddset
	kill
*/

# include <dirent.h>
/*
	opendir, readdir, closedir
*/

# include <sys/ioctl.h>
/*
	ioctl
*/

# include <termios.h>
/*
	tcsetattr, tcgetattr
*/

# include <curses.h>
# include <term.h>
/*
	extern char PC;
	extern char * UP;
	extern char * BC;
	extern short ospeed;

	int tgetent(char *bp, const char *name);
	int tgetflag(char *id);
	int tgetnum(char *id);
	char *tgetstr(char *id, char **area);
	char *tgoto(const char *cap, int col, int row);
	int tputs(const char *str, int affcnt, int (*putc)(int));
*/

#endif

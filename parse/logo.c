/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 06:58:15 by macbookpro        #+#    #+#             */
/*   Updated: 2024/01/12 14:18:42 by junkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_logo_sub(void)
{
	char	*yellow;
	char	*white;

	yellow = "\033[93m";
	white = "\033[0m";
	printf("%s║   ██║█  █╗██║   ██║   ██║██  ██║   ██║    █████╗ ████████╗█████"\
	"███║██████╗  ██║      ██║                 ║%s\n", yellow, white);
	printf("%s║   ██║ ██╔╝██║   ██║   ██║╚██ ██║   ██║     ════╝ ╚═════██║██╔══"\
	"═██║██╔═══╝  ██║      ██║                 ║%s\n", yellow, white);
	printf("%s║   ██║ ██║ ██║████████╗██║ ╚████║████████╗        ████████║██║  "\
	" ██║████████╗████████╗████████╗           ║%s\n", yellow, white);
	printf("%s║   ╚═╝ ╚═╝ ╚═╝╚═══════╝╚═╝  ╚═══╝╚═══════╝        ╚═══════╝╚═╝  "\
	" ╚═╝╚═══════╝╚═══════╝╚═══════╝           ║%s\n", yellow, white);
	printf("%s║                                                                "\
	"                                          ║%s\n", yellow, white);
	printf("%s║                                                                "\
	"             .made by junkim2 & minjacho  ║%s\n", yellow, white);
	printf("%s║                                                                "\
	"                                          ║%s\n", yellow, white);
	printf("%s╚════════════════════════════════════════════════════════════════"\
	"══════════════════════════════════════════╝%s\n", yellow, white);
	printf("\n");
}

void	print_logo(void)
{
	char	*yellow;
	char	*white;

	yellow = "\033[93m";
	white = "\033[0m";
	printf("%s╔════════════════════════════════════════════════════════════════"\
	"══════════════════════════════════════════╗%s\n", yellow, white);
	printf("%s║                                                                "\
	"                                          ║%s\n", yellow, white);
	printf("%s║   Welcome to K-Minishell project!                              "\
	"                                          ║%s\n", yellow, white);
	printf("%s║                                                                "\
	"                                          ║%s\n", yellow, white);
	printf("%s║                                                                "\
	"                                          ║%s\n", yellow, white);
	printf("%s║   ██      ██╗████████╗██     ██╗████████╗        ████████╗██╗  "\
	" ██╗████████╗██╗      ██╗                 ║%s\n", yellow, white);
	printf("%s║   ███    ███║  ═██╔══╝███    ██║  ═██╔══╝        ██╔═════╝██║  "\
	" ██║██╔═════╝██║      ██║                 ║%s\n", yellow, white);
	print_logo_sub();
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 06:58:15 by macbookpro        #+#    #+#             */
/*   Updated: 2024/01/05 19:22:21 by junkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    print_logo(void)
{
	const char	*red;
	const char	*yellow;
	const char	*white;

	red = "\033[31m";
	yellow = "\033[93m";
	white = "\033[0m";
	printf("%s╔══════════════════════════════════════════════════════════════════════════════════════════════════════════╗%s\n", yellow, white);
	printf("%s║                                                                                                          ║%s\n", yellow, white);
	printf("%s║   Welcome to K-Minishell project!                                                                        ║%s\n", yellow, white);
	printf("%s║                                                                                                          ║%s\n", yellow, white);
	printf("%s║                                                                                                          ║%s\n", yellow, white);
	printf("%s║   ██      ██╗████████╗██     ██╗████████╗        ████████╗██╗   ██╗████████╗██╗      ██╗                 ║%s\n", yellow, white);
	printf("%s║   ███    ███║  ═██╔══╝███    ██║  ═██╔══╝        ██╔═════╝██║   ██║██╔═════╝██║      ██║                 ║%s\n", yellow, white);
    printf("%s║   ██║█  █╗██║   ██║   ██║██  ██║   ██║    █████╗ ████████╗████████║██████╗  ██║      ██║                 ║%s\n", yellow, white);
	printf("%s║   ██║ ██╔╝██║   ██║   ██║╚██ ██║   ██║     ════╝ ╚═════██║██╔═══██║██╔═══╝  ██║      ██║                 ║%s\n", yellow, white);
	printf("%s║   ██║ ██║ ██║████████╗██║ ╚████║████████╗        ████████║██║   ██║████████╗████████╗████████╗           ║%s\n", yellow, white);
	printf("%s║   ╚═╝ ╚═╝ ╚═╝╚═══════╝╚═╝  ╚═══╝╚═══════╝        ╚═══════╝╚═╝   ╚═╝╚═══════╝╚═══════╝╚═══════╝           ║%s\n", yellow, white);
	printf("%s║                                                                                                          ║%s\n", yellow, white);
	printf("%s║                                                                             .made by junkim2 & minjacho  ║%s\n", yellow, white);
	printf("%s║                                                                                                          ║%s\n", yellow, white);
	printf("%s╚══════════════════════════════════════════════════════════════════════════════════════════════════════════╝%s\n", yellow, white);
	printf("\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendonc <dmendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 08:22:28 by anfreire          #+#    #+#             */
/*   Updated: 2023/01/06 20:22:49 by dmendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

extern int	g_exit;

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_exit = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	sig_handler_one(int signum)
{
	if (signum == SIGINT)
	{
		g_exit = 130;
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	back_slash(int sig)
{
	if (sig == SIGQUIT)
	{
		g_exit = 131;
		printf("Quit (core dumped)\n");
	}
}

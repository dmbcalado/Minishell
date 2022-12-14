/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendonc <dmendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 10:51:25 by anfreire          #+#    #+#             */
/*   Updated: 2023/01/06 20:23:17 by dmendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

extern int	g_exit;

void	exit_shell(t_data *data)
{
	if (!data->line)
		exit_shell_sig(1);
}

void	exit_shell_sig(int sig)
{
	if (sig == 1)
		printf("exit\n");
	exit(0);
}

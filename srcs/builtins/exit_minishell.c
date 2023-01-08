/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratinhosujo <ratinhosujo@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:53:19 by anfreire          #+#    #+#             */
/*   Updated: 2023/01/08 16:03:35 by ratinhosujo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

extern int	g_exit;

static int	ft_isdigit_n_dash(int arg)
{
	if ((arg >= 48 && arg <= 57) || arg == '-')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

static int	is_string_digit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit_n_dash(str[i]))
			return (0);
	}
	return (1);
}

void	free_exit(t_data *data)
{
	int	size;

	size = data->cmd.cmd_nbr + data->built.builtin_n;
	if (size == 0)
		free(data->ids.inp_list);
	free(data->ids.id);
}


void	exit_minishell(t_data *data)
{
	int	args;

	args = 0;
	while (data->par_line[args])
		args++;
	free_exit(data);
	if (args >= 2)
	{
		if (!is_string_digit(data->par_line[1]))
		{
			printf("minishell: exit: %s: numeric \
			argument required\n", data->par_line[1]);
			g_exit = 2;
		}
		else if (args == 2)
		{
			printf("exit\n");
			g_exit = (char)ft_atoi(data->par_line[1]);
			printf("g exit : %d", g_exit);
		}
		else
			printf("minishell: exit: too many arguments\n");
		free_line_info(data);
	}
	else
	{
		free_line_info(data);
		printf("exit\n");
	}
	exit(g_exit);
}

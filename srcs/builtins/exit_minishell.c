/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendonc <dmendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:53:19 by anfreire          #+#    #+#             */
/*   Updated: 2023/01/07 01:58:17 by dmendonc         ###   ########.fr       */
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

static int	return_exit(char *str)
{
	int	digit;

	digit = (char)ft_atoi(str);
	if (digit)
		return (digit);
	return (0);
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
	int	ret;
	int	args;

	ret = 0;
	args = 0;
	while (data->par_line[args])
		args++;
	free_line_info(data);
	free_exit(data);
	if (args >= 2)
	{
		if (!is_string_digit(data->par_line[1]))
		{
			printf("minishell: exit: %s: numeric \
			argument required\n", data->par_line[1]);
			ret = 2;
		}
		else if (args == 2)
		{
			printf("exit\n");
			ret = return_exit(data->par_line[1]);
		}
		printf("minishell: exit: too many arguments\n");
		ret = 1;
	}
	else
		printf("exit\n");
	exit(ret);
}

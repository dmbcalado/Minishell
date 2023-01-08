/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratinhosujo <ratinhosujo@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:35:12 by dmendonc          #+#    #+#             */
/*   Updated: 2023/01/08 15:20:43 by ratinhosujo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

extern int	g_exit;

void	run_child_bultin(t_data *data, int index, int jndex, int i)
{
	if (index == 0)
		piping_first(data, index);
	else if (index == data->cmd.cmd_nbr + data->built.builtin_n - 1)
		piping_last(data, index);
	else
	{
		redirecting_input(data, index);
		redirecting_output(data, index);
	}
	execve_builtin(data, jndex, i);
	free_for_builtins(data);
	exit(g_exit);
}

void	exec_builtin(t_data *data, int index, int i)
{
	int	jndex;

	jndex = builtin_detector(data, data->par_line[i]);
	if (jndex < 2 && jndex >= 0)
	{
		data->ids.id[index] = fork();
		if (data->ids.id[index] == 0)
			run_child_bultin(data, index, jndex, i);
		data->redir.r_counter++;
	}
	else if (jndex == 2)
		env(data);
	else if (jndex == 3)
		export(data);
	else if (jndex == 4)
		unset(data, data->par_line[1]);
	else if (jndex == 5)
		b_cd(data, index);
	else if (jndex == 6)
		run_minishell(data, index);
	else if (jndex == 7)
		exit_minishell(data);
}

void	execve_builtin(t_data *data, int jndex, int i)
{
	if (jndex == 0)
		b_echo(data, i);
	else if (jndex == 1)
		b_pwd();
}

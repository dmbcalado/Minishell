/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendonc <dmendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:53:40 by dmendonc          #+#    #+#             */
/*   Updated: 2022/12/29 16:58:39 by dmendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	redirect_fds(int infd, int outfd)
{
	dup2 (infd, STDIN_FILENO);
	dup2 (outfd, STDOUT_FILENO);
}

void	run_processes(t_data *data, int index)
{
	data->ids.id = fork();
	if (data->ids.id == 0)
	{
		if (index == 0)
			run_first_child(data, index);
		else if (index == data->cmd.cmd_nbr - 1)
			run_last_child(data, index);
		else
			run_middle_child(data, index);
		execve(data->paths.path_cmd[index], data->cmd.cmdx[index], data->envp);
	}
	else
		run_father (data, index);
}

void	run_father(t_data *data, int index)
{
	close (data->ids.pfd[index][1]);
	wait (NULL);
	if (data->ids.out_fd == STDOUT_FILENO)
		return ;
	else
		dup2 (data->ids.pfd[index][0], STDIN_FILENO);
}

void	pipes(t_data *data)
{
	int	i;

	i = -1;
	printf("cmd_nbr %d\n", data->cmd.cmd_nbr);
	while (++i < data->cmd.cmd_nbr)
	{
		if (acessing_cmd (data, i) == 0)
		{
			printf ("%s: command not found.\n", data->paths.path_cmd[i]);
			return ;
		}
		if (pipe (data->ids.pfd[i]) != 0)
			return ;
		run_processes (data, i);
	}
	free_cmds(data);
}

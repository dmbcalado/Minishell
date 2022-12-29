/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendonc <dmendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 07:30:34 by anfreire          #+#    #+#             */
/*   Updated: 2022/12/29 16:52:43 by dmendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	run_one_cmd(t_data *data, int in_fd, int out_fd)
{
	if (acessing_cmd (data, 0) == 0)
	{
		printf ("%s: command not found.\n", data->paths.path_cmd[0]);
		return ;
	}
	data->ids.id = fork();
	if (data->ids.id == 0)
		child_one(data, in_fd, out_fd);
	else
	{
		waitpid(data->ids.id, NULL, 0);
		free_cmds (data);
		return ;
	}
}

void	child_one(t_data *data, int in_fd, int out_fd)
{
	if (in_fd > 0)
	{
		dup2 (in_fd, STDIN_FILENO);
		close (in_fd);
	}
	if (out_fd > 1)
	{
		dup2 (out_fd, STDOUT_FILENO);
		close (out_fd);
	}
	if (execve (data->paths.path_cmd[0], data->cmd.cmdx[0], data->envp) < 0)
		perror("Error\n");
}

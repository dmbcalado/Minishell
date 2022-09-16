/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendonc <dmendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 07:30:34 by anfreire          #+#    #+#             */
/*   Updated: 2022/09/16 02:38:41 by dmendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	run_one_cmd(t_data *data, int *in_fd, int *out_fd)
{
	if (acessing_cmd (data, 0) == 0)
	{
		printf ("%s: command not found.\n", data->paths.path_cmd[0]);
		return ;
	}
	if (pipe (data->ids.pfd[0]) != 0)
	{
		printf ("ERROR on piping.\n");
		exit (0);
	}
	data->ids.id = fork();
	if (data->ids.id == 0)
	{
		if(in_fd[0] > 0)
			dup2 (in_fd[0], STDIN_FILENO);
		execve (data->paths.path_cmd[0], data->cmd.cmdx[0], data->envp);
	}
	else
	{
		waitpid(data->ids.id, NULL, 0);
		if (out_fd[0] != STDOUT_FILENO)
			dup2 (out_fd[0], STDOUT_FILENO);
		free_cmds (data);
		return ;
	}
}

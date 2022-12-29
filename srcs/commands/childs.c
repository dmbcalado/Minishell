/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendonc <dmendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:56:31 by dmendonc          #+#    #+#             */
/*   Updated: 2022/12/29 16:58:16 by dmendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	run_first_child(t_data *data, int index)
{
	close (data->ids.pfd[index][0]);
	if (data->ids.inp_list[index] != STDIN_FILENO)
	{
		dup2 (data->ids.inp_list[index], STDIN_FILENO);
		data->redir.input_c++;
	}
	if (data->ids.outp_list[index] != STDOUT_FILENO)
	{
		dup2 (data->ids.outp_list[index], STDOUT_FILENO);
		data->redir.output_c++;
	}
	else
		dup2(data->ids.pfd[index][1], STDOUT_FILENO);
}

void	run_last_child(t_data *data, int index)
{
	close (data->ids.pfd[index - 1][1]);
	if (data->ids.inp_list[index] == STDIN_FILENO)
		dup2(data->ids.pfd[index - 1][0], STDIN_FILENO);
	else
	{
		dup2(data->ids.inp_list[index], STDIN_FILENO);
		data->redir.input_c++;
	}
	if (data->ids.outp_list[index] != STDOUT_FILENO)
	{
		dup2 (data->ids.outp_list[index], STDOUT_FILENO);
		data->redir.output_c++;
	}
}

void	run_middle_child(t_data *data, int index)
{
	close (data->ids.pfd[index - 1][1]);
	close (data->ids.pfd[index][0]);
	if (data->ids.inp_list[index] == STDIN_FILENO)
		dup2(data->ids.pfd[index - 1][0], STDIN_FILENO);
	else
	{
		dup2(data->ids.inp_list[index], STDIN_FILENO);
		data->redir.input_c++;
	}
	if (data->ids.outp_list[index] == STDOUT_FILENO)
		dup2(data->ids.pfd[index - 1][0], STDOUT_FILENO);
	else
	{
		dup2(data->ids.outp_list[index], STDOUT_FILENO);
		data->redir.output_c++;
	}
}

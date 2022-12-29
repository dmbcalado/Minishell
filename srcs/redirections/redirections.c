/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendonc <dmendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 21:31:48 by dmendonc          #+#    #+#             */
/*   Updated: 2022/12/29 00:41:02 by dmendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

//------------------------------------------------------------------------------
// args: i as par_line[i], index has in wich cmd index, flag has flag = 1 : </>
//																flag = 2 : <</>>
// task: reads the fd and if different then the standard, opens with the
// corresponding flags.
//------------------------------------------------------------------------------

int	exec_redirect(t_data *data, int index, int i)
{
	int	save;

	save = redir_detector(data, data->par_line[i]);
	if (save == 2)
	{
		data->ids.inp_list[index] = open (data->redir.input[index], O_RDONLY);
		if (data->ids.inp_list[index] < 0)
		{
			printf("Error: the file %s does not exist.", \
			data->redir.input[index]);
			return (-1);
		}
	}
	else if (exec_out_redirect(data, index, i, save) < 0)
		return (-1);
	return (0);
}

int	exec_out_redirect(t_data *data, int index, int i, int save)
{
	if (save == 4)
	{
		data->ids.outp_list[index] = open(data->redir.output[index], O_CREAT \
		| O_TRUNC | O_RDWR, 0644);
		if (data->ids.outp_list[index] < 1)
		{
			printf("Error: the file %s had issues on open().", \
			data->redir.output[index]);
			return (-1);
		}
		else
			printf("sucessefully opened %s\n", data->redir.output[index]);
	}
	else if (exec_append_redir(data, index, i, save) < 0)
		return (-1);
	return (1);
}

int	exec_append_redir(t_data *data, int index, int i, int save)
{
	if (save == 5)
	{
		data->ids.outp_list[index] = open(data->redir.output[index], O_CREAT \
		| O_APPEND | O_RDWR, 0644);
		if (data->ids.outp_list[index] < 0)
		{
			printf("Error: the file %s had issues on open().", \
			data->redir.output[index]);
			return (-1);
		}
		else
			printf("sucessefully opened %s\n\n", data->redir.output[index]);
	}
	return (1);
}

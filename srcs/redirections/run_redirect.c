/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendonc <dmendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 21:31:48 by dmendonc          #+#    #+#             */
/*   Updated: 2022/09/16 02:44:52 by dmendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

//------------------------------------------------------------------------------
// args: i as par_line[i], index has in wich cmd index, flag has flag = 1 : </>
//																flag = 2 : <</>>
// task: sets all counters to zero,
//------------------------------------------------------------------------------

void	redirect(t_data *data)
{
	int i;
	int	index;
	int	size;
	int save;
	
	
	index = 0;
	size = data->cmd.cmd_nbr + data->built.builtin_n;
	reset_counters(data);
	while(++index < size)
	{
		while(data->par_line[i] && redir_detector (data, data->par_line[++i]) != 1)
		{
			if (redir_detector (data, data->par_line[i]) > 1)
			{
				save = parse_redirec(data, i, index);
				exec_redirect(data, index, save);
			}
			i++;
		}
	}
	reset_counters(data);
}
 
//------------------------------------------------------------------------------
// args: i as par_line[i], index has in wich cmd index, flag has flag = 1 : </>
//																flag = 2 : <</>>
// task: reads the fd and if different then the standard, opens with the
// corresponding flags.
//------------------------------------------------------------------------------

void	exec_redirect(t_data *data, int index, int save)
{
	count_redir (data , index);
	if (save == 1)
	{
		data->ids.inp_list[index][data->redir.input_c] = open (data->redir.input[index][data->redir.input_c], O_RDONLY);
		if(data->ids.inp_list[index][data->redir.input_c] < 0)
		{
			printf("Error: the file %s does not exist.", data->redir.input[index][data->redir.input_c]);
			return ;
		}
		data->redir.input_c++;
	}
	if (save == 4)
	{
		data->ids.outp_list[index][data->redir.output_c] = open(data->redir.output[index][data->redir.output_c], O_CREAT | O_TRUNC | O_RDWR);
		if(data->ids.outp_list[index][data->redir.output_c] < 0)
		{
			printf("Error: the file %s had issues on open().",data->redir.input[index][data->redir.input_c]);
			return ;
		}
		else
			printf("sucessefully opened %s\n\n",data->redir.input[index][data->redir.input_c]);
		data->redir.output_c++;
	}
}
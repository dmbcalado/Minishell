/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendonc <dmendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 21:31:48 by dmendonc          #+#    #+#             */
/*   Updated: 2022/09/17 05:04:35 by dmendonc         ###   ########.fr       */
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
	int	index;
	int	size;
	int i;
	int	flag;
	int	ret;
	
	index = -1;
	size = data->cmd.cmd_nbr + data->built.builtin_n;
	flag = 0;
	i = 0;
	while(++index < size)
	{
		while(data->par_line[i])
		{
			ret = redir_detector (data, data->par_line[i]);
			if (ret == 1)
				break;
			if (ret > 1)
			{
				if (ret < 4 && flag == 0)
				{
					//treat all infiles that exist but are just bridges
					i = find_i_for_infile(data, index);
					extract_input(data, index, i + 1);
					exec_redirect(data, index, i);
					flag++;
				}
				else if (flag == 0)
				{
					//treat all outfiles that exist but are just bridges
					i = find_i_for_outfile(data, index);
					extract_output(data, index, i + 1);
					exec_redirect(data, index, i);
					flag++;
				}
			}
			i++;
		}
		flag = 0;
	}
}

//------------------------------------------------------------------------------
// args: i as par_line[i], index has in wich cmd index, flag has flag = 1 : </>
//																flag = 2 : <</>>
// task: reads the fd and if different then the standard, opens with the
// corresponding flags.
//------------------------------------------------------------------------------

void	exec_redirect(t_data *data, int index, int i)
{
	int save;

	save = redir_detector(data, data->par_line[i]);
	if (save == 2)
	{
		data->ids.inp_list[index] = open (data->redir.input[index], O_RDONLY);
		if(data->ids.inp_list[index] < 0)
		{
			printf("Error: the file %s does not exist.", data->redir.input[index]);
			return ;
		}	
	}
	if (save == 3)
	{
		data->ids.inp_list[index] = open (data->redir.input[index], O_RDONLY); // VER FLAGS HEREDOC
		if(data->ids.inp_list[index] < 0)
		{
			printf("Error: the file %s does not exist.", data->redir.input[index]);
			return ;
		}	
	}
	if (save == 4)	//output
	{
		data->ids.outp_list[index] = open(data->redir.output[index], O_CREAT | O_TRUNC | O_RDWR, 0644);
		if(data->ids.outp_list[index] < 1)
		{
			printf("Error: the file %s had issues on open().",data->redir.output[index]);
			return ;
		}
		else
			printf("sucessefully opened %s\n",data->redir.output[index]);
	}
	if (save == 5)	//output
	{
		data->ids.outp_list[index] = open(data->redir.output[index], O_CREAT | O_TRUNC | O_RDWR); // VER FLAGS APPEND
		if(data->ids.outp_list[index] < 0)
		{
			printf("Error: the file %s had issues on open().",data->redir.output[index]);
			return ;
		}
		else
			printf("sucessefully opened %s\n\n",data->redir.output[index]);
	}
}
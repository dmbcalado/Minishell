/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendonc <dmendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 21:31:48 by dmendonc          #+#    #+#             */
/*   Updated: 2022/12/29 00:19:17 by dmendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

//------------------------------------------------------------------------------
// args: i as par_line[i], index has in wich cmd index, flag has flag = 1 : </>
//																flag = 2 : <</>>
// task: sets all counters to zero
//------------------------------------------------------------------------------

int	redirect(t_data *data)
{
	int	i;
	int	ret;
	int	index;

	i = -1;
	index = -1;
	while (++index < data->size)
	{
		while (data->par_line[++i])
		{
			ret = redir_detector(data, data->par_line[i]);
			if (ret == 1)
				break ;
			if (ret > 1)
			{
				if (apply_redirect(data, i, index, ret) == -1)
					return (-1);
			}
		}
		data->ids.flag_i = 0;
		data->ids.flag_o = 0;
	}
	return (1);
}

int	apply_redirect(t_data *data, int i, int index, int ret)
{
	if (ret < 4 && data->ids.flag_i == 0)
	{
		i = find_i_for_infile(data, index);
		data->ids.flag_i = redirect_input(data, i, index);
		if (data->ids.flag_i == -1)
			return (-1);
	}
	if (ret > 3 && data->ids.flag_o == 0)
	{
		i = find_i_for_outfile(data, index);
		data->ids.flag_o = redirect_output(data, i, index);
		if (data->ids.flag_o == -1)
			return (-1);
	}
	return (1);
}

int	redirect_input(t_data *data, int i, int index)
{
	int	ret;

	if (bridge_infiles(data, index, i) < 0)
		return (-1);
	ret = redir_detector(data, data->par_line[i]);
	if (ret == 2)
	{
		extract_input(data, index, i + 1);
		if (exec_redirect(data, index, i) < 0)
			return (-1);
	}
	else
	{
		extract_hdockey(data, i + 1);
		heredoc(data, index);
	}
	return (1);
}

int	redirect_output(t_data *data, int i, int index)
{
	if (bridge_outfiles(data, index, i) < 0)
		return (-1);
	extract_output(data, index, i + 1);
	if (exec_redirect(data, index, i) < 0)
		return (-1);
	return (1);
}

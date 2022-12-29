/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bridges.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendonc <dmendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:20:36 by ratinhosujo       #+#    #+#             */
/*   Updated: 2022/12/29 01:10:28 by dmendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	bridge_infiles(t_data *data, int index)
{
	int	count;
	int	i;
	int	ret;

	i = 0;
	count = -1;
	while (++count <= index)
	{
		while (data->par_line[i])
		{
			ret = redir_detector (data, data->par_line[i]);
			if (ret == 1)
				break ;
			if (bridging_infiles(data, index, i, ret) < 0)
				return (-1);
			i++;
		}
	}
	return (1);
}

int	bridge_outfiles(t_data *data, int index)
{
	int	count;
	int	i;
	int	ret;

	i = 0;
	count = -1;
	while (++count <= index)
	{
		while (data->par_line[i])
		{
			ret = redir_detector (data, data->par_line[i]);
			if (ret == 1)
				break ;
			if (bridging_outfiles(data, i, ret) < 0)
				return (-1);
			i++;
		}
	}
	return (1);
}

int	bridging_infiles(t_data *data, int index, int i, int ret)
{
	if (ret > 1)
	{
		if (ret == 2 && i != data->redir.last)
		{
			if (open(data->par_line[i + 1], O_RDONLY) < 0)
			{
				printf("Error: the file %s does not exist.", \
				data->par_line[i + 1]);
				return (-1);
			}
		}
		if (ret == 3 && i != data->redir.last)
		{
			extract_hdockey(data, i + 1);
			heredoc(data, index);
		}
	}
	return (1);
}

int	bridging_outfiles(t_data *data, int i, int ret)
{
	if (ret > 1)
	{
		if (ret == 4 && i != data->redir.last)
		{
			if (open(data->par_line[i + 1], O_CREAT | O_TRUNC, 0644) < 0)
				return (-1);
		}
		else if (ret == 5 && i != data->redir.last)
		{
			if (open(data->par_line[i + 1], O_CREAT | O_APPEND, 0644) < 0)
				return (-1);
		}
	}
	return (1);
}

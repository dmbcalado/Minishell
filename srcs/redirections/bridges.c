/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bridges.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratinhosujo <ratinhosujo@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:20:36 by ratinhosujo       #+#    #+#             */
/*   Updated: 2022/09/19 18:27:52 by ratinhosujo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	bridge_infiles(t_data *data, int index, int last)
{
	int	count;
	int	i;
	int	ret;
	
	i = 0;
	count = -1;
	printf("introu\n");
	while(++count <= index)
	{
		while(data->par_line[i])
		{
			printf("introu 2\n");
			ret = redir_detector (data, data->par_line[i]);
			if (ret == 1)
				break;
			if (ret > 1)
			{
				if (ret < 4 && i != last)
				{
					printf("introu 3\n");
					if(open(data->par_line[i + 1], O_RDONLY) < 0)
					{
						printf("Error: the file %s does not exist.", data->par_line[i + 1]);
						return (-1);
					}
				}
			}
			i++;
		}
	}
	return (1);
}

int	bridge_outfiles(t_data *data, int index, int last)
{
	int	count;
	int	i;
	int	ret;
	
	i = 0;
	count = -1;
	printf("entrou\n");
	while(++count <= index)
	{
		while(data->par_line[i])
		{
			ret = redir_detector (data, data->par_line[i]);
			if (ret == 1)
				break;
			if (ret > 1)
			{
				printf("entrou2\n");
				if (ret > 3 && i != last)
				{
					printf("entrou3\n");
					if(open(data->par_line[i + 1], O_CREAT | O_TRUNC , 0644) < 0)
						return (-1);
				}
			}
			i++;
		}
	}
	return (1);
}
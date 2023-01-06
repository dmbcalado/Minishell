/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendonc <dmendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:47:33 by dmendonc          #+#    #+#             */
/*   Updated: 2023/01/06 22:50:20 by dmendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

extern int	g_exit;

void	popullate_echo(t_data *data, int i)
{
	while (data->par_line[++i])
	{
		if (ft_strncmp(data->par_line[i], "-n", 3) == 0)
			continue ;
		if (ft_strncmp(data->par_line[i], "|", 2) == 0 || \
		ft_strncmp(data->par_line[i], "<", 2) == 0 || \
		ft_strncmp(data->par_line[i], ">", 2) == 0 || \
		ft_strncmp(data->par_line[i], "<<", 3) == 0 || \
		ft_strncmp(data->par_line[i], ">>", 3) == 0)
			break ;
		printf("%s", data->par_line[i]);
		if (data->par_line[i + 1] != NULL)
			printf(" ");
	}
}

void	b_echo(t_data *data, int i)
{
	char	flag[3];

	flag[0] = '-';
	flag[1] = 'n';
	flag[2] = '\0';
	if (!data->par_line[i + 1])
	{
		printf("\n");
		return ;
		g_exit = 0;
	}
	popullate_echo(data, i);
	if (ft_strncmp(data->par_line[i + 1], flag, 3) != 0)
		printf("\n");
	g_exit = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendonc <dmendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 00:57:24 by dmendonc          #+#    #+#             */
/*   Updated: 2022/12/29 01:43:22 by dmendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	run_envp(t_data *data, int *smal, int i, int s)
{
	int	j;

	j = -1;
	while (data->envp[i][++j] != 0)
	{
		if (data->envp[i][j] < data->envp[s][j])
		{
			if (find_in_list(smal, i) >= 0)
			{
				s = i;
				break ;
			}
		}
		else if (data->envp[i][j] == data->envp[s][j] && i != s)
			continue ;
		else
			break ;
	}
}

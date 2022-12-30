/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendonc <dmendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 02:50:09 by dmendonc          #+#    #+#             */
/*   Updated: 2022/12/30 02:50:24 by dmendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	joining(t_data *data, char *str, int i_p)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	j = -1;
	count = p_size(data, str, i_p) + 1;
	data->paths.test_cmd = (char *)malloc(count * sizeof(char));
	data->paths.test_cmd[count - 1] = '\0';
	while (data->paths.paths[i_p][++i])
		data->paths.test_cmd[i] = data->paths.paths[i_p][i];
	while (str[++j])
		data->paths.test_cmd[i++] = str[j];
}

void	get_line(t_data *data)
{
	if (data->andre.flag == 1)
		echo_with_n_flag(data);
	if (data->line)
		free(data->line);
	data->line = NULL;
	data->line = readline("$ ▶ ");
	exit_shell(data);
	if (data->line[0] != '\0')
		add_history(data->line);
}
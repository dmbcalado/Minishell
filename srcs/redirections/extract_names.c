/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_names.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratinhosujo <ratinhosujo@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 21:02:23 by dmendonc          #+#    #+#             */
/*   Updated: 2022/09/19 15:45:02 by ratinhosujo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	extract_input(t_data *data, int index, int i)
{
	int	j;

	j = 0;
	while (data->par_line[i][j])
		j++;
	free(data->redir.input[index]);
	data->redir.input[index] = (char *)malloc((j + 1) * sizeof(char));
	data->redir.input[index][j] = 0;
	j = -1;
	while (data->par_line[i][++j])
		data->redir.input[index][j] = data->par_line[i][j];
	printf("input: %s\n", data->redir.input[index]);
}

void	extract_output(t_data *data, int index, int i)
{
	int	j;

	j = 0;
	while (data->par_line[i][j])
			j++;
	free(data->redir.output[index]);
	data->redir.output[index] = (char *)malloc((j + 1) * sizeof(char));
	data->redir.output[index][j] = 0;
	j = -1;
	while (data->par_line[i][++j])
		data->redir.output[index][j] = data->par_line[i][j];
	printf("output: %s\n", data->redir.output[index]);
}
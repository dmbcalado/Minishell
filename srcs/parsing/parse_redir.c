/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendonc <dmendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 18:39:32 by dmendonc          #+#    #+#             */
/*   Updated: 2022/09/16 01:59:59 by dmendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"
//------------------------------------------------------------------------------
// args: i as par_line[i], index has in wich cmd index.
// task: Checks redirections, if yes, checks if theres a second one, then 
// extracts the name of the file using extract_output().
//------------------------------------------------------------------------------

int	parse_redirec (t_data *data, int i, int index)
{
	if (data->par_line[i][0] == data->redir.redir_lib[1]) // <
	{
		if (data->par_line[i][1] == 0)
		{
			extract_input(data, i + 1, index, 1);
			return (1);
		}
		else if (data->par_line[i][0] == data->redir.redir_lib[1]) // <<
		{
			extract_input(data, i + 1, index, 2);
			return (2);
		}
	}
	if (data->par_line[i][0] == data->redir.redir_lib[2]) // >
	{
		if (data->par_line[i][1] == 0)
		{
			extract_output(data, i + 1, index, 1);
			return (3);
		}
		else if (data->par_line[i][0] == data->redir.redir_lib[2]) // >>
		{
			extract_output(data, i + 1, index, 2);
			return (4);
		}
	}
	return (0);
}

//------------------------------------------------------------------------------
// args: i as par_line[i], index has in wich cmd index, flag has flag = 1 : <
//																flag = 2 : <<
// task: allocates data->redir.input[index] then copys the par_line[i].
//				   data->redir.heredoc[index] then copys the par_line[i].
//------------------------------------------------------------------------------

void	extract_input(t_data *data, int i, int index, int flag)
{
	int	j;

	j = 0;
	if (flag == 1)
	{
		while (data->par_line[i][j])
			j++;
		data->redir.input[index][data->redir.input_c] = (char *)malloc((j + 1) * sizeof(char));
		data->redir.input[index][data->redir.input_c][j] = 0;
		j = -1;
		while (data->par_line[i][++j])
			data->redir.input[index][data->redir.input_c][j] = data->par_line[i][j];
	}
	else if (flag == 2)
	{
		while (data->par_line[i][j])
			j++;
		data->redir.heredoc[index][data->redir.heredoc_c] = (char *)malloc((j + 1) * sizeof(char));
		data->redir.heredoc[index][data->redir.heredoc_c][j] = 0;
		j = -1;
		while (data->par_line[i][++j])
			data->redir.heredoc[index][data->redir.heredoc_c][j] = data->par_line[i][j];
		printf("heredoc: %s\n", data->redir.input[index][data->redir.heredoc_c]);
	}
}

//------------------------------------------------------------------------------
// args: i as par_line[i], index has in wich cmd index, flag has flag = 1 : >
//																flag = 2 : >>
// task: allocates data->redir.output[index] then copys the par_line[i].
//				   data->redir.append[index] then copys the par_line[i].
//------------------------------------------------------------------------------

void	extract_output(t_data *data, int i, int index, int flag)
{
	int	j;

	j = 0;
	if (flag == 1)
	{
		while (data->par_line[i][j])
			j++;
		data->redir.output[index][data->redir.output_c] = (char *)malloc((j + 1) * sizeof(char));
		data->redir.output[index][data->redir.output_c][j] = 0;
		j = -1;
		while (data->par_line[i][++j])
			data->redir.output[index][data->redir.output_c][j] = data->par_line[i][j];
		data->redir.output_c++;
		printf("output: %s\n", data->redir.output[index][data->redir.output_c]);
	}
	else if (flag == 2)
	{
		while (data->par_line[i][j])
			j++;
		data->redir.append[index][data->redir.append_c] = (char *)malloc((j + 1) * sizeof(char));
		data->redir.append[index][data->redir.append_c][j] = 0;
		j = -1;
		while (data->par_line[i][++j])
			data->redir.append[index][data->redir.append_c][j] = data->par_line[i][j];
		data->redir.append_c++;
		printf("append: %s\n", data->redir.input[index][data->redir.append_c]);
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_allocs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendonc <dmendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 07:30:34 by anfreire          #+#    #+#             */
/*   Updated: 2022/12/28 22:44:15 by dmendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	parse_alloc(t_data *data)
{
	data->par_line = spliting(data->line, ' ');
	create_lists(data);
	count_line(data);
	alloc_cmds(data);
	alloc_redirections(data);
	if (data->built.builtin_n > 0)
	{
		data->built.builtin = (char ***)malloc((data->built.builtin_n + 1) \
		* sizeof(char **));
		data->built.builtin[data->built.builtin_n] = NULL;
	}
}

void	count_line(t_data *data)
{
	int	i;

	i = 0;
	set_counters(data);
	while (data->par_line[i])
	{
		if (builtin_detector (data, data->par_line[i]) > 0)
			data->built.builtin_n++;
		else if (cmd_detector (data, data->par_line[i]) == 1)
			data->cmd.cmd_nbr++;
		else if (redir_detector (data, data->par_line[i]) > 1)
		{
			if (redir_detector (data, data->par_line[i]) == 2)
				data->redir.input_n++;
			if (redir_detector (data, data->par_line[i]) == 3)
				data->redir.heredoc_n++;
			if (redir_detector (data, data->par_line[i]) == 4)
				data->redir.output_n++;
			if (redir_detector (data, data->par_line[i]) == 5)
				data->redir.append_n++;
		}
		i++;
	}
}

// -----------------------------------------------------------------------------
// Fully allocates data.ids.pfd[size] and allocates both char *** for  cmdx
// and paths.path_cmd.
// -----------------------------------------------------------------------------

void	alloc_cmds(t_data *data)
{
	int	i;

	i = -1;
	if (data->cmd.cmd_nbr > 0)
	{
		data->ids.pfd = (int **)malloc((data->cmd.cmd_nbr + 1) * sizeof(int *));
		data->cmd.cmdx = (char ***)malloc((data->cmd.cmd_nbr + 1) \
		* sizeof(char **));
		data->paths.path_cmd = (char **)malloc((data->cmd.cmd_nbr + 1) \
		* sizeof(char *));
		while (++i < data->cmd.cmd_nbr)
			data->ids.pfd[i] = (int *)malloc(2 * sizeof(int));
		data->ids.pfd[data->cmd.cmd_nbr] = NULL;
		data->cmd.cmdx[data->cmd.cmd_nbr] = NULL;
		data->paths.path_cmd[data->cmd.cmd_nbr] = NULL;
	}
}

// -----------------------------------------------------------------------------
// Fully allocates redir.input[size] and allocates both char ** for 
// collecting the file name of the input (or EOF), and the filename output.
// -----------------------------------------------------------------------------

void	alloc_redirections(t_data *data)
{
	int	i;

	data->ids.flag_i = 0;
	data->ids.flag_o = 0;
	data->size = data->cmd.cmd_nbr + data->built.builtin_n;
	if (data->size == 0 && data->redir.heredoc_n > 0)
	{
		data->ids.inp_list = (int *)malloc(sizeof(int));
		extract_hdockey(data, 1);
		heredoc(data, 0);
	}
	data->redir.input = (char **)malloc((data->size + 1) * sizeof(char *));
	data->redir.output = (char **)malloc((data->size + 1) * sizeof(char *));
	data->ids.inp_list = (int *)malloc(data->size * sizeof(int));
	data->ids.outp_list = (int *)malloc(data->size * sizeof(int));
	data->redir.input[data->size] = NULL;
	data->redir.output[data->size] = NULL;
	i = -1;
	while (++i < data->size)
	{
			data->redir.input[i] = (char *)malloc(sizeof(char));
			data->redir.output[i] = (char *)malloc(sizeof(char));
			data->ids.inp_list[i] = STDIN_FILENO;
			data->ids.outp_list[i] = STDOUT_FILENO;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendonc <dmendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 07:30:34 by anfreire          #+#    #+#             */
/*   Updated: 2022/09/16 02:43:46 by dmendonc         ###   ########.fr       */
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
    data->line = NULL;
    if (data->line)
    {
        free(data->line);
        data->line = NULL;
    }
    data->line = readline("$ > ");
	exit_shell(data);
    if (data->line[0] != '\0')
        add_history(data->line);
}

void	count_line(t_data *data)
{
	int	i;

	i = 0;
	data->cmd.cmd_nbr = 0;
	data->redir.input_n = 0;
	data->redir.output_n = 0;
	data->redir.append_n = 0;
	data->redir.heredoc_n = 0;
	data->built.builtin_n = 0;
	while(data->par_line[i] && redir_detector (data, data->par_line[i]) != 1)
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

void	parse_alloc(t_data *data)
{
	data->par_line = spliting(data->line, ' ');
	create_lists(data);
	count_line(data);
	alloc_cmds(data);
	alloc_redirections(data);
	if (data->built.builtin_n > 0)
	{
		data->built.builtin = (char ***)malloc((data->built.builtin_n + 1) * sizeof(char **));
		data->built.builtin[data->built.builtin_n] = NULL;
	}
	//check for env variables.
	//check for redirections
	//check for fullpaths.
}

void	alloc_cmds(t_data *data)
{
	int	i;

	i = -1;
	if (data->cmd.cmd_nbr > 0)
	{
		data->ids.pfd = (int **)malloc((data->cmd.cmd_nbr + 1) * sizeof(int *));
		data->cmd.cmdx = (char ***)malloc((data->cmd.cmd_nbr + 1) * sizeof(char **));	
		data->paths.path_cmd = (char **)malloc((data->cmd.cmd_nbr + 1) * sizeof(char *));
		while (++i < data->cmd.cmd_nbr)
			data->ids.pfd[i] = (int *)malloc(2 * sizeof(int));
		data->ids.pfd[data->cmd.cmd_nbr] = NULL; 
		data->cmd.cmdx[data->cmd.cmd_nbr] = NULL;
		data->paths.path_cmd[data->cmd.cmd_nbr] = NULL;
	}
}

void	alloc_redirections(t_data *data)
{
	int	i;
	int	size;
	int index;
	size = data->cmd.cmd_nbr + data->built.builtin_n;
	data->redir.input = (char ***)malloc((size + 1) * sizeof(char **));
	data->redir.output = (char ***)malloc((size + 1) * sizeof(char **));
	data->redir.append = (char ***)malloc((size + 1) * sizeof(char **));
	data->redir.heredoc = (char ***)malloc((size + 1) * sizeof(char **));
	data->ids.inp_list = (int **)malloc((size + 1) * sizeof(int *));
	data->ids.outp_list = (int **)malloc((size + 1) * sizeof(int *));
	data->redir.input[size] = NULL;
	data->ids.inp_list[size] = NULL;
	index = -1;
	while(++index < size)
	{
		count_redir(data, index);
		data->redir.input[index] = (char **)malloc((data->redir.input_n + 1) * sizeof(char *));
		data->ids.inp_list[index] = (int *)malloc(data->redir.input_n * sizeof(int));
		data->redir.output[index] = (char **)malloc((data->redir.output_n + 1) * sizeof(char *));
		data->ids.outp_list[index] = (int *)malloc(data->redir.output_n * sizeof(int));
		data->redir.append[index] = (char **)malloc((data->redir.append_n + 1) * sizeof(char *));
		data->redir.heredoc[index] = (char **)malloc((data->redir.heredoc_n + 1) * sizeof(char *));
		data->redir.input[index][data->redir.input_n] = NULL;
		data->redir.output[index][data->redir.output_n] = NULL;
		data->redir.append[index][data->redir.append_n] = NULL;
		data->redir.heredoc[index][data->redir.heredoc_n] = NULL;
		i = -1;
		while(++i < data->redir.input_n)
			data->ids.inp_list[index][i] = STDIN_FILENO;
		i = -1;
		while(++i < data->redir.output_n)
			data->ids.outp_list[index][i] = STDOUT_FILENO;
	}
}


void	count_redir(t_data *data , int index)
{
	int	i;

	i = 0;
	while(i < index)
	{
		data->cmd.cmd_nbr = 0;
		data->redir.input_n = 0;
		data->redir.output_n = 0;
		data->redir.append_n = 0;
		data->redir.heredoc_n = 0;
		data->built.builtin_n = 0;
		while( redir_detector (data, data->par_line[++i]) != 1)
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
		}
		i++;	
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendonc <dmendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 07:30:34 by anfreire          #+#    #+#             */
/*   Updated: 2022/09/13 19:25:36 by dmendonc         ###   ########.fr       */
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

char	*get_line(t_data *data)
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
    return (data->line);
}

void	count_line(t_data *data)
{
	int	i;

	i = -1;
	data->cmd.cmd_nbr = 0;
	data->built.builtin_n = 0;
	data->redir.redir_n = 0;
	while(data->par_line[++i])
	{
		if (builtin_detector (data, data->par_line[i]) > 1)
			data->built.builtin_n++;
		else if (cmd_detector (data, data->par_line[i]) == 1)
			data->cmd.cmd_nbr++;
		else if (redir_detector (data, data->par_line[i]) > 0)
			data->redir.redir_n++;
	}
}

void	parse_alloc(t_data *data)
{
	data->par_line = spliting(data->line, ' ');
	create_lists(data);
	count_line(data);
	alloc_cmds(data);
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
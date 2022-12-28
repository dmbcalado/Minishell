/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendonc <dmendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 22:26:54 by dmendonc          #+#    #+#             */
/*   Updated: 2022/12/28 22:38:31 by dmendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

// -----------------------------------------------------------------------------
// This function creates the builtins list to check if its a built in.
// -----------------------------------------------------------------------------

void	create_lists(t_data *data)
{
	data->built.builtins = (char **)malloc(8 * sizeof(char *));
	data->redir.redir_lib = (char *)malloc(4 * sizeof(char));
	get_str(data, "echo", 0);
	get_str(data, "pwd", 1);
	get_str(data, "env", 2);
	get_str(data, "export", 3);
	get_str(data, "unset", 4);
	get_str(data, "cd", 5);
	get_str(data, "pwd", 6);
	data->built.builtins[7] = NULL;
	data->redir.redir_lib[3] = 0;
	data->redir.redir_lib[0] = '|';
	data->redir.redir_lib[1] = '<';
	data->redir.redir_lib[2] = '>';
	data->ids.in_fd = STDIN_FILENO;
	data->ids.out_fd = STDOUT_FILENO;
}

void	get_str(t_data *data, char *str, int index)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	data->built.builtins[index] = (char *)malloc((i + 1) * sizeof(char));
	data->built.builtins[index][i] = 0;
	i = -1;
	while (str[++i] != 0)
		data->built.builtins[index][i] = str[i];
}

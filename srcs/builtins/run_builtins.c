/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendonc <dmendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:35:12 by dmendonc          #+#    #+#             */
/*   Updated: 2022/12/29 01:43:18 by dmendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	exec_builtin(t_data *data, int i)
{
	int	jndex;

	jndex = builtin_detector(data, data->par_line[i]);
	if (jndex == 2)
		env(data);
	else if (jndex == 3)
		export(data, data->built.b_counter);
	else if (jndex == 4)
		unset(data, data->par_line[1]);
}

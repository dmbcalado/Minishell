/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendonc <dmendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 02:13:18 by dmendonc          #+#    #+#             */
/*   Updated: 2022/09/16 02:13:45 by dmendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void reset_counters(t_data *data)
{
	data->redir.input_c = 0;
	data->redir.output_c = 0;
	data->redir.append_c = 0;
	data->redir.heredoc_c = 0;
}
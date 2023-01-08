/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratinhosujo <ratinhosujo@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 03:34:10 by anfreire          #+#    #+#             */
/*   Updated: 2023/01/08 14:54:15 by ratinhosujo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

extern int	g_exit;

void	b_pwd(void)
{
	char	buff[FILENAME_MAX];

	getcwd(buff, FILENAME_MAX);
	printf("%s\n", buff);
	g_exit = 0;
}

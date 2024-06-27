/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 21:20:33 by qang              #+#    #+#             */
/*   Updated: 2024/06/27 21:23:17 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "a.h"

int	pwd(char **args, t_entab *table)
{
	if (length(args) == 1 || args[1][0] != '-')
		printf("%s\n", get_var("PWD", table)->val);
	else
	{
		printf("pwd: too many arguments\n");
		return (1);
	}
	return (0);
}

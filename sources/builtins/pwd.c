/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 21:20:33 by qang              #+#    #+#             */
/*   Updated: 2024/07/17 00:35:10 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdio.h>

int	pwd(char **args, t_entab *table);

int	pwd(char **args, t_entab *table)
{
	if (length(args) == 1 || args[1][0] != '-')
		printf("%s\n", get_var("PWD", table)->val);
	return (0);
}

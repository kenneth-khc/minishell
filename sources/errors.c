/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:57:43 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/21 15:35:52 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "parser.h"
#include "ft_dprintf.h"

void	error(const char *str)
{
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}


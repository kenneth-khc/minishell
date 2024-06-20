/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 21:42:07 by kecheong          #+#    #+#             */
/*   Updated: 2024/06/20 21:43:21 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>

void	_log(FILE *FILE,
			const char *FILENAME,
			const char *FUNC,
			int LINE,
			char *format, ...)
{
	fprintf(FILE, "%s:%s:%d: ", FILENAME, FUNC, LINE);
	va_list args;
	va_start(args, format);
	vfprintf(FILE, format, args);
	va_end(args);
	fprintf(FILE, "\n");
}


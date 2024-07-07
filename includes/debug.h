/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:20:48 by kecheong          #+#    #+#             */
/*   Updated: 2024/06/20 21:43:30 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include <assert.h>
# include <stdarg.h>
# include <stdio.h>
# include "tokens.h"
# include <stdbool.h>

# define cout(...) _log(stdout, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
# define cerr(...) _log(stderr, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)

# define PARSE_SUCCESS 1
# define PARSE_FAIL 0


void	_log(FILE *FILE,
			const char *FILENAME,
			const char *FUNC,
			int LINE,
			char *format, ...);

#endif

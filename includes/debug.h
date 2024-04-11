/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:20:48 by kecheong          #+#    #+#             */
/*   Updated: 2024/04/11 11:54:59 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include <assert.h>
# include <stdarg.h>
# include <stdio.h>

#define cout(msg) _log(stdout, __FILE__, __FUNCTION__, __LINE__, msg)
#define cerr(msg) _log(stderr, __FILE__, __FUNCTION__, __LINE__, msg)

void	_log(FILE *FILE, const char *FILENAME, const char *FUNC, int LINE, char *msg)
{
	fprintf(FILE, "%s:%s:%d: %s\n", FILENAME, FUNC, LINE, msg);
}

void	print_tokens(t_Token_list *tokens);

#endif
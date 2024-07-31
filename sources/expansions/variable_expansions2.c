/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansions2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 10:12:55 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/24 19:13:25 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "expansions.h"
#include "definitions.h"

static bool
special_parameter(char *dollar);

static void
expand_special_parameters(t_Chunk_List *chunks, char *dollar);

static void
expand_parameter(t_Chunk_List *chunks, t_entab *env, char *dollar);

/**
 * We check for special shell parameters, then check for variables
 * Variables should start with an underscore (_) or alphabets
 * If it is not valid, we preserve the dollar character
 **/
bool	do_variable_expansion(t_Chunk_List *chunks, t_entab *env,
	t_Range *p)
{
	char	*extracted;

	extracted = ft_extract_substring(p->start, p->end - 1);
	add_chunk(chunks, extracted);
	if (special_parameter(p->end))
	{
		expand_special_parameters(chunks, p->end);
		p->end += 2;
		return (true);
	}
	else if (is_identifier_start(p->end))
	{
		expand_parameter(chunks, env, p->end);
		p->end = ft_strpbrk(p->end + 1, is_not_identifier);
		if (chunks->tail->str)
			return (true);
		else
			return (false);
	}
	else
	{
		extracted = ft_extract_substring(p->end, p->end);
		add_chunk(chunks, extracted);
		p->end += 1;
	}
	return (false);
}

/**
* These are the only special shell parameters implemented
* $? gives the last exit status
* $0 gives the name of the shell
* $$ gives the current process ID
**/
static bool	special_parameter(char *dollar)
{
	return (dollar[1] == '?'
		|| dollar[1] == '0'
		|| dollar[1] == '$');
}

int	get_exit_status(void);

static void	expand_special_parameters(t_Chunk_List *chunks, char *dollar)
{
	char	*value;

	value = NULL;
	if (dollar)
	{
		if (dollar[1] == '?')
			value = ft_itoa(get_exit_status());
		else if (dollar[1] == '0')
			value = ft_strdup(SHELL);
		else if (dollar[1] == '$')
			value = ft_itoa(getpid());
		add_chunk(chunks, value);
	}
}

static void	expand_parameter(t_Chunk_List *chunks, t_entab *env, char *dollar)
{
	char	*key_start;
	char	*key_end;
	char	*key;
	char	*value;

	key_start = dollar + 1;
	key_end = ft_strpbrk(key_start, is_not_identifier) - 1;
	key = ft_extract_substring(key_start, key_end);
	if (key)
	{
		value = copy_var_val(key, env);
		add_chunk(chunks, value);
	}
	else
		value = NULL;
	free(key);
}

char	*copy_var_val(char *key, t_entab *env)
{
	t_envar	*envar;
	char	*value;

	envar = get_var(key, env);
	if (envar && (envar->state & DISPLAY))
		value = envar->val;
	else
		value = NULL;
	if (value)
		value = ft_strdup(value);
	return (value);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:47:00 by kecheong          #+#    #+#             */
/*   Updated: 2024/08/05 09:18:48 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "definitions.h"
#include "libft.h"

t_String	*get_expansion(char *key_start, t_entab *env);

void	do_expansion(t_Expansion_List *expansions, t_Token *token,
					char *dollar, t_entab *env)
{
	t_String	*key;
	char		*key_start;
	char		*key_end;
	t_String	*value;
	t_Expansion	*new_expansion;

	key_end = ft_strpbrk(dollar + 1, is_not_identifier) - 1;
	key_start = ft_extract_substring(dollar, key_end);
	key = stringify(key_start);
	value = get_expansion(dollar + 1, env);
	if (value)
	{
		new_expansion = create_expansion(key, value,
				dollar - token->lex->start);
	}
	else
	{
		new_expansion = create_expansion(key, stringify(""),
				dollar - token->lex->start);
	}
	add_expansion(expansions, new_expansion);
	update_token_lexeme(token, expansions);
}

void	parameter_expansion(t_Expansion_List *expansions, t_Token *token,
							t_entab *env)
{
	t_Range		p;

	p.start = token->lex->start;
	p.end = token->lex->end;
	while (*p.start)
	{
		if (is_expansion(p.start, &token->quotes))
		{
			if (is_identifier_start(p.start))
			{
				do_expansion(expansions, token, p.start, env);
				if (expansions->tail && expansions->tail->end)
					p.start = expansions->tail->end + 1;
				else
					p.start++;
			}
		}
		else
			p.start++;
	}
}

t_String	*get_expansion(char *key_start, t_entab *env)
{
	char	*key_end;
	char	*key;
	char	*value;

	key_end = ft_strpbrk(key_start, is_not_identifier) - 1;
	key = ft_extract_substring(key_start, key_end);
	if (key)
		value = copy_var_val(key, env);
	else
		value = NULL;
	return (stringify(value));
}

t_Expansion	*get_next_expansion(t_Expansion_List *expansions, bool reset)
{
	static t_Expansion	*next_expansion = NULL;

	if (reset)
	{
		next_expansion = NULL;
		return (NULL);
	}
	if (next_expansion == expansions->tail)
	{
		next_expansion = NULL;
		return (NULL);
	}
	else if (next_expansion == NULL)
	{
		next_expansion = expansions->head;
	}
	else if (next_expansion)
	{
		next_expansion = next_expansion->next;
	}
	while (next_expansion && next_expansion->offset == -1)
		next_expansion = next_expansion->next;
	return (next_expansion);
}

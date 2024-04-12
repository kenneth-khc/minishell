/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:25:32 by kecheong          #+#    #+#             */
/*   Updated: 2024/04/12 08:38:43 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

enum e_Token_types
{
	WORD = 256,
	PIPE,				// |
	AND_AND,			// &&
	OR_OR,				// ||
	LESSER,				// <
	LESSER_LESSER,		// <<
	GREATER,			// >
	GREATER_GREATER,	// >>
	STAR
};

typedef struct s_Token
{
	struct s_Token	*next;
	int				type;
	const char		*lexeme;
}	t_Token;

typedef struct s_Token_list
{
	struct s_Token	*head;
	struct s_Token	*tail;
}	t_Token_list;

t_Token	*create_token(int type, const char *lexeme);
void	add_token(t_Token_list *tokens, t_Token *token);
void	print_tokens(t_Token_list *tokens);

#endif
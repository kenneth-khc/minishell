/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:25:32 by kecheong          #+#    #+#             */
/*   Updated: 2024/04/15 16:35:19 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

enum e_Token_types
{
	WORD = 256,
	PIPE,				// |
	OR_OR,				// ||
	AND_AND,			// &&
	LESSER,				// <
	LESSER_LESSER,		// <<
	GREATER,			// >
	GREATER_GREATER,	// >>
	STAR,				// *
	OPEN_PARAN,			// (
	CLOSE_PARAN,		// )
	END_OF_LINE,		// \0
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
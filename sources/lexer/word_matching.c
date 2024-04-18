/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_matching.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 21:47:29 by kecheong          #+#    #+#             */
/*   Updated: 2024/04/18 21:53:28 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "lexer.h"
#include "libft.h"

/* 	I WILL READ THE DOCUMENTATION AND HANDLE QUOTES PROPERLY THIS TIME */

void	match_word(t_Lexer *scanner, t_Token_list *tokens)
{
	while (!is_metacharacter(*scanner->lookahead))
		scanner->lookahead++;
	add_token(tokens, create_token(WORD,
		extract_substring(scanner->start, scanner->lookahead)));
		
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_matching3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:02:27 by kecheong          #+#    #+#             */
/*   Updated: 2024/04/18 17:49:09 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "tokens.h"
#include <stdio.h>

void	match_end_of_line(t_Lexer *scanner, t_Token_list *tokens)
{
	(void)scanner;
	add_token(tokens, create_token(END_OF_LINE, NULL));
}

void	skip_comment(t_Lexer *scanner)
{
	while (*scanner->lookahead != '\n')
		scanner->lookahead++;
	scanner->start = scanner->lookahead;
}

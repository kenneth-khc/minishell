/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:44:52 by kecheong          #+#    #+#             */
/*   Updated: 2024/04/18 21:39:35 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "tokens.h"
# include <stdbool.h>

typedef struct s_Lexer
{
	char	*line;
	char	*start;
	char	**history;
}	t_Lexer;

typedef struct s_Match_Table
{
	const char			*lexeme;
	enum e_Token_Types	type;
}	t_Match_Table;

bool	is_metacharacter(const char c);
bool	is_blank(const char c);
char			*extract_substring(const char *start, const char *end);
bool			end_of_line(t_Token *token);
void			skip_whitespaces(t_Lexer *scanner);
void			skip_comment(t_Lexer *scanner);
void			match(t_Lexer *scanner, t_Token_list *tokens);
void			match_word(t_Lexer *scanner, t_Token_list *tokens);

void			match_quotes(t_Lexer *scanner, t_Token_list *tokens);
bool			is_quote_terminated(t_Lexer *scanner);
void			prompt_until_terminated(t_Lexer *scanner, bool terminated);
char			*get_quoted_word(t_Lexer *scanner);


#endif

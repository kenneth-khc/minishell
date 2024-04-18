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
	char	*lookahead;
	char	**history;
}	t_Lexer;

#define TOKEN_MATCHERS 7
typedef struct s_Matcher
{
	char	start;
	void	(*match_function)();
}	t_Matcher;

bool	is_metacharacter(const char c);
bool	is_blank(const char c);
char			*extract_substring(const char *start, const char *end);

t_Matcher		*init_matchers(void);
bool			end_of_line(t_Token *token);
void			skip_whitespaces(t_Lexer *scanner);
void			skip_comment(t_Lexer *scanner);
void			match(t_Lexer *scanner, t_Matcher *matchers, t_Token_list *tokens);
void			match_bar(t_Lexer *scanner, t_Token_list *tokens);
void			match_lesser(t_Lexer *scanner, t_Token_list *tokens);
void			match_greater(t_Lexer *scanner, t_Token_list *tokens);
void			match_and(t_Lexer *scanner, t_Token_list *tokens);
void			match_word(t_Lexer *scanner, t_Token_list *tokens);
void			match_end_of_line(t_Lexer *scanner, t_Token_list *tokens);

void			match_quotes(t_Lexer *scanner, t_Token_list *tokens);
bool			is_quote_terminated(t_Lexer *scanner);
void			prompt_until_terminated(t_Lexer *scanner, bool terminated);
char			*get_quoted_word(t_Lexer *scanner);


#endif
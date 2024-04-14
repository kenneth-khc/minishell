/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:44:52 by kecheong          #+#    #+#             */
/*   Updated: 2024/04/15 21:15:28 by kecheong         ###   ########.fr       */
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

#define TOKEN_MATCHERS 5
typedef struct s_Matcher
{
	char	start;
	void	(*match_function)();
}	t_Matcher;

t_Matcher		*init_matchers(void);
t_Token_list	scan(char **line);
bool			end_of_line(t_Token *token);
void			skip_whitespaces(t_Lexer *scanner);
void			match(t_Lexer *scanner, t_Matcher *matchers, t_Token_list *tokens);
void			match_bar(t_Lexer *scanner, t_Token_list *tokens);
void			match_lesser(t_Lexer *scanner, t_Token_list *tokens);
void			match_greater(t_Lexer *scanner, t_Token_list *tokens);
void			match_and(t_Lexer *scanner, t_Token_list *tokens);
void			match_word(t_Lexer *scanner, t_Token_list *tokens);
void			match_quotes(t_Lexer *scanner, t_Token_list *tokens);
void			match_end_of_line(t_Lexer *scanner, t_Token_list *tokens);

#endif
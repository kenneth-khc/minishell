/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:44:52 by kecheong          #+#    #+#             */
/*   Updated: 2024/04/11 11:54:34 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "tokens.h"

t_Token_list	scan(const char *line);
t_Token	*create_token(int type, const char *lexeme);
void	add_to_list(t_Token_list *tokens, t_Token *token);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:44:52 by kecheong          #+#    #+#             */
/*   Updated: 2024/04/12 10:44:07 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "tokens.h"

t_Token_list	scan(const char *line);
void			scan_bar(const char **line, t_Token_list *tokens);
void			scan_lesser(const char **ptr_to_line, t_Token_list *tokens);
void			scan_greater(const char **ptr_to_line, t_Token_list *tokens);
void			scan_word(const char **ptr_to_line, t_Token_list *tokens);
void			scan_quotes(const char **ptr_to_line, t_Token_list *tokens);


#endif
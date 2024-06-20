/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:53:46 by kecheong          #+#    #+#             */
/*   Updated: 2024/06/20 21:31:28 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "tokens.h"
#include <stdbool.h>
#include "ast.h"

#define PARSE_SUCCESS 1
#define PARSE_FAIL 0

typedef struct s_Parser
{
	t_Token		*current_token;
	t_Node		*root;

}	t_Parser;

void	parse(t_Parser *parser, t_Token_List *tokens);
bool	parse_command(t_Parser *parser);
bool	parse_simple_command(t_Parser *parser);
bool	parse_command_prefix(t_Parser *parser);
bool	parse_command_suffix(t_Parser *parser, t_Exec_Node *command_node);
t_Exec_Node	*parse_command_name(t_Parser *parser);
bool	parse_command_word(t_Parser *parser);
bool	parse_io_here(t_Parser *parser);
bool	parse_io_redirect(t_Parser *parser);
bool	expect(t_Token *token, enum e_Token_Types type);
void	consume(t_Parser *parser);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:53:46 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/17 01:13:13 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>
# include "tokens.h"
# include "tree.h"
# include "env.h"

typedef struct s_Parser
{
	t_Token_List	*tokens; // list of tokens
	t_Token			*token; // current token the parser is looking at
	t_entab			*envtab; // environment table
	bool			syntax_ok;
}	t_Parser;

void			init_parser(t_Parser *parser, t_Token_List *tokens, t_entab *env);
t_Node			*parse(t_Parser *parser);
t_Node			*parse_subshell(t_Parser *parser);
t_Node			*parse_list(t_Parser *parser);
t_Node			*parse_pipe_sequence(t_Parser *parser);
t_Node			*parse_and_or(t_Parser *parser);
t_Node			*parse_pipe_sequence(t_Parser *parser);
t_Node			*parse_simple_command(t_Parser *parser);
t_Node			*parse_command_prefix(t_Parser *parser);
t_Node			*parse_command_suffix(t_Parser *parser,
					t_Node *prefix, t_Exec_Node *exec_node);
t_Exec_Node		*parse_command_name(t_Parser *parser); // what is the difference
bool			parse_command_word(t_Parser *parser); // between a name and a word?
t_Node			*parse_io_redirect(t_Parser *parser);
bool			expect(t_Parser *parser, enum e_Token_Types expected, const char *errmsg);
bool			accept(t_Parser *parser, enum e_Token_Types type);
t_Token			*consume(t_Parser *parser);

// Utils
bool			is_redirection_token(t_Token *token);
bool			is_and_or_token(t_Token *token);
bool			is_and_or(t_Parser *parser);
enum e_Token_Types	peek(t_Parser *parser);

#endif

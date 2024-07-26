/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:53:46 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/21 17:48:03 by kecheong         ###   ########.fr       */
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
	t_entab			*envtab; // environment table
	t_Token_List	*tokens; // list of tokens
	t_Token			*token; // current token the parser is looking at
	t_Token			*consumed;
	bool			syntax_ok;
}	t_Parser;

// Init parser with token stream and env table
void			init_parser(t_Parser *parser, t_Token_List *tokens,
					t_entab *env);

// Parsing procedures
t_Node			*parse(t_Parser *parser);
t_Node			*parse_subshell(t_Parser *parser);
t_Node			*parse_list(t_Parser *parser);
t_Node			*parse_pipe_sequence(t_Parser *parser);
t_Node			*parse_and_or(t_Parser *parser);
t_Node			*parse_simple_command(t_Parser *parser);
t_Node			*parse_io_redirect(t_Parser *parser);
void			flag_last_heredoc(t_Node *root);

// Utils
t_Token_Type	peek(t_Parser *parser);
bool			expect(t_Parser *parser, enum e_Token_Types expected,
					const char *errmsg);
bool			accept(t_Parser *parser, enum e_Token_Types type);
t_Token			*consume(t_Parser *parser);
void			syntax_error(t_Parser *parser, const char *err_msg,
					t_Token *got);
bool			is_redirection_token(t_Token *token);
bool			is_io_redirect(t_Parser *parser);

#endif

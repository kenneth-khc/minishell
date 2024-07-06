/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:53:46 by kecheong          #+#    #+#             */
/*   Updated: 2024/06/26 17:48:52 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "tokens.h"
#include <stdbool.h>
#include "tree.h"
# include "a.h"

typedef struct s_Parser
{
	t_Token		*token; // current token the parser is looking at
	t_Token		*lookahead; // 1 token after current token
	t_entab		*envtab; // environment table
	t_Node		*root; // root of the tree constructed so far
}	t_Parser;

t_Node			*parse(t_Parser *parser, t_Token_List *tokens);
t_Node			*parse_complete_command(t_Parser *parser);
t_Node			*parse_pipe_sequence(t_Parser *parser);
t_Node			*parse_and_or(t_Parser *parser);
t_Node			*parse_pipe_sequence(t_Parser *parser);
t_Node			*parse_simple_command(t_Parser *parser);
t_Node			*parse_command_prefix(t_Parser *parser);
t_Node			*parse_command_suffix(t_Parser *parser, t_Exec_Node *exec_node);
t_Exec_Node		*parse_command_name(t_Parser *parser); // what is the difference
bool			parse_command_word(t_Parser *parser); // between a name and a word?
t_Node			*parse_io_redirect(t_Parser *parser);
t_Node			*parse_io_here(t_Parser *parser);
t_Node			*parse_io_file(t_Parser *parser);
t_Redir_Node	*input_redir(t_Parser *parser, int flags);
t_Redir_Node	*output_redir(t_Parser *parser, int flags);
bool			expect(t_Parser *parser, enum e_Token_Types expected);
bool			accept(t_Parser *parser, enum e_Token_Types type);
void			consume(t_Parser *parser);

// Utils
bool			is_redirection_token(t_Token *token);
bool			is_and_or_token(t_Token *token);
enum e_Token_Types	peek_token(t_Token *token);

#endif

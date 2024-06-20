/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:16:06 by kecheong          #+#    #+#             */
/*   Updated: 2024/06/20 21:44:00 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ast.h"
#include "tokens.h"
#include <stdlib.h>
#include "debug.h"
#include <stdbool.h>

int	times_expected = 0;
int times_consumed = 0;

void	parse(t_Parser *parser, t_Token_List *tokens)
{(void)parser;(void)tokens;
	cout("start parser");
	parser->current_token = tokens->head;

	while (parser->current_token->type != END_OF_LINE
			&& parse_command(parser))
	{
		;
	}
	
	// cout("Root: %s", parser->root->value);
	cout("Root: %s", ((t_Exec_Node *)parser->root)->command);
	cout("Args1: %s", ((t_Exec_Node *)parser->root)->args[0]);
	cout("Args2: %s", ((t_Exec_Node *)parser->root)->args[1]);
	cout("end parser");
	cout("times expected: %d", times_expected);
	cout("times consumed: %d", times_consumed);
	exit(EXIT_SUCCESS);
}

bool	parse_command(t_Parser *parser)
{
	return (parse_simple_command(parser));
}

bool	parse_simple_command(t_Parser *parser)
{
	if (parse_command_prefix(parser))
	{
		if (parse_command_word(parser))
		{
			parse_command_suffix(parser, NULL);
		}
		return (PARSE_SUCCESS); // todo: fix return
	}
	else if (parse_command_name(parser)) // "echo hello world" goes here
		return (PARSE_SUCCESS);
	else
		return (PARSE_SUCCESS); // todo: add more expressions
}

bool	parse_command_word(t_Parser *parser)
{ (void)parser;return(PARSE_FAIL);
}

bool	parse_command_prefix(t_Parser *parser)
{
	return parse_io_redirect(parser);
}

t_Exec_Node	*parse_command_name(t_Parser *parser)
{
	t_Exec_Node	*exec_node;

	exec_node = NULL;
	if (expect(parser->current_token, WORD))
	{
		// exec_node = create_ast_node(Command_Node);
		exec_node = create_exec_node(parser->current_token->lexeme, NULL);
		consume(parser);
		while (parse_command_suffix(parser, exec_node))
			;
	}
	parser->root = (t_Node *)exec_node; // temp
	return (exec_node);
}

bool	parse_command_suffix(t_Parser *parser, t_Exec_Node *exec_node)
{(void)exec_node;
	if (expect(parser->current_token, WORD))
	{
		add_exec_arguments(exec_node, parser->current_token->lexeme);
		consume(parser);
		return (PARSE_SUCCESS);
	}
	return (PARSE_FAIL);
}

bool	parse_io_redirect(t_Parser *parser)
{
	// parse_io_file(parser);
	return parse_io_here(parser);
}

bool	parse_io_here(t_Parser *parser)
{
	if (expect(parser->current_token, LESSER_LESSER))
	{
		consume(parser);
		// search for here_end
		if (expect(parser->current_token, WORD))
		{
			consume(parser);
			return (PARSE_SUCCESS);
		}
		else
		{
			cerr("not here_end");
			return (PARSE_SUCCESS);
		}
	}
	else
	{
		cerr("not heredoc");
		return (PARSE_FAIL);
	}
}

bool	expect(t_Token *token, enum e_Token_Types expected_type)
{
	times_expected++;
	if (token->type == expected_type)
	{
		cout("Expected %s", token_enum_to_str(token));
		return (PARSE_SUCCESS);
	}
	else
	{
		cout("Unexpected %s", token_enum_to_str(token));
		return (PARSE_FAIL);
	}
}

void	consume(t_Parser *parser)
{
	times_consumed++;
	cout("Consumed %s", token_enum_to_str(parser->current_token));
	parser->current_token = parser->current_token->next;
}

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
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	times_expected = 0;
int times_consumed = 0;

t_Node	*parse(t_Parser *parser, t_Token_List *tokens)
{(void)parser;(void)tokens;
	cout("start parser");
	t_Node	*root;

	parser->current = tokens->head;
	parser->lookahead = parser->current->next;
	while (parser->current->type != END_OF_LINE)
	{
		root = parse_command(parser);
	}

	// cout("Root: %s", parser->root->value);
	cout("end parser");
	cout(">>> %s\n", ((t_Redir_Node *)root->left)->file);
	cout(">>> %d\n", ((t_Redir_Node *)root->left)->oldfd);
	t_Redir_Node *temp = (t_Redir_Node *)root->left;
	t_Redir_Node *this = (t_Redir_Node *)temp->next_node;
	cout(">>> %s\n", this->file);
	cout(">>> %d\n", this->oldfd);
	cout("times expected: %d", times_expected);
	cout("times consumed: %d", times_consumed);
	exit(EXIT_SUCCESS);
	return (root);
}

t_Node	*parse_command(t_Parser *parser)
{
	t_Node	*node;

	node = parse_simple_command(parser);
	return (node);
}

t_Node	*parse_simple_command(t_Parser *parser)
{
	t_Node	*node;

	if (parse_command_prefix(parser))
	{
		if (parse_command_word(parser))
		{
			parse_command_suffix(parser, NULL);
		}
		return (NULL);
	}
	node = (t_Node *)parse_command_name(parser);
	return (node);
	// else if (parse_command_name(parser)) // "echo hello world" goes here
	// 	return (PARSE_SUCCESS);
	// else
	return (NULL); // todo: add more expressions
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
	if (expect(parser->current, WORD))
	{
		// exec_node = create_ast_node(Command_Node);
		exec_node = create_exec_node(parser->current->lexeme, NULL);
		consume(parser);
		while (parse_command_suffix(parser, exec_node))
			;
	}
	parser->root = (t_Node *)exec_node; // temp
	return (exec_node);
}

bool	parse_command_suffix(t_Parser *parser, t_Exec_Node *exec_node)
{
	t_Redir_Node	*top;

	top = parse_io_redirect(parser);
	if (top)
	{
		//top->next_node = (t_Node *)exec_node;
		exec_node->left = (t_Node *)top;
		return (top);
	}
	if (expect(parser->current, WORD))
	{
		add_exec_arguments(exec_node, parser->current->lexeme);
		consume(parser);
		return (PARSE_SUCCESS);
	}
	return (PARSE_FAIL);
}

t_Redir_Node	*parse_io_redirect(t_Parser *parser)
{
	t_Redir_Node	*node;
	node = parse_io_file(parser);
	if (node)
		return (node);
	// else // todo: fix heredoc
	// 	return parse_io_here(parser);
	else
		return (NULL);
}

t_Redir_Node	*parse_io_file(t_Parser *parser)
{
	t_Redir_Node	*node;

	node = NULL;
	if (expect(parser->current, LESSER))
	{
		node = input_redir(parser);
	}
	else if (expect(parser->current, GREATER))
	{
		node = output_redir(parser);
	}
	return (node);
}

t_Redir_Node	*input_redir(t_Parser *parser)
{
	t_Redir_Node	*node;

	consume(parser);
	if (expect(parser->current, WORD))
	{
		consume(parser);
		node = create_redir_node(STDIN_FILENO, parser->current->lexeme,
				O_CREAT, 0666);
	}
	else
		node = NULL;
	return (node);
}

t_Redir_Node	*output_redir(t_Parser *parser)
{
	t_Redir_Node	*node;

	consume(parser);
	if (expect(parser->current, WORD))
	{
		node = create_redir_node(STDOUT_FILENO, parser->current->lexeme,
				O_CREAT, 0666);
		consume(parser);
	}
	else
		node = NULL;
	return (node);
}

bool	parse_io_here(t_Parser *parser)
{
	if (expect(parser->current, LESSER_LESSER))
	{
		consume(parser);
		// search for here_end
		if (expect(parser->current, WORD))
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
	cout("Consumed %s", token_enum_to_str(parser->current));
	parser->current = parser->current->next;
	parser->lookahead = parser->current->next;
}


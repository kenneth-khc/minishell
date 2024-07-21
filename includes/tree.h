/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 21:06:03 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/18 17:48:42 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H
# include <sys/types.h>
# include <stdbool.h>
# include "env.h"

typedef enum e_Node_Type
{
	Exec_Node = 1,
	Argument_Node,
	Redir_Node,
	Pipe_Node,
	AND_AND_NODE,
	OR_OR_NODE,
	ASS_NODE,
	SUBSHELL_NODE
}	t_Node_Type;

/**
 * Generic node type to be passed around
 * Check the type and typecast as appropriately to access its contents
 * Access the next node through the left pointer
 * Right node is only used for operators expecting 2 operands
 */
typedef struct s_Node
{
	enum e_Node_Type	type;
	struct s_Node		*left;
	struct s_Node		*right;
}	t_Node;

t_Node	*node(enum e_Node_Type type);

/**
 * Node for executing commands
 */
typedef struct s_Exec_Node
{
	enum e_Node_Type	type;
	struct s_Node		*left;
	struct s_Node		*right;
	t_entab				*table;
	const char			*command; // Name of the command to execute
	int					arg_count; // Number of arguments in the command
	const char			**args; // Args of the cmd, first one being the cmdname
}	t_Exec_Node;

t_Exec_Node		*create_exec_node(const char *cmd_name, t_entab *envtab);
void			add_exec_arguments(t_Exec_Node *exec_node, const char *arg);

/**
 * Node for redirection
 */
typedef enum e_Direction
{
	INPUT,
	OUTPUT
}	t_Direction;

typedef struct s_Redir_Node
{
	enum e_Node_Type	type;
	struct s_Node		*left;
	struct s_Node		*right;
	t_entab				*table;
	enum e_Direction	direction; // is it input or output redirection
	int					oldfd; // the fd to be replaced
	int					flags; // O_CREAT, O_APPEND etc
	mode_t				mode; // permission bits for READ WRITE EXECUTE
	const char			*file; // name of the file to open
	bool				heredoc;
	char				*delim;
}	t_Redir_Node;

t_Redir_Node	*redir_node(t_entab *env);

typedef struct s_Parser	t_Parser;
t_Redir_Node	*create_redir_node(int oldfd, const char *filename,
					int flags, mode_t mode);

/**
 * Node for piping
 */
typedef struct s_Pipe_Node
{
	enum e_Node_Type	type;
	struct s_Node		*left; // Left exec node to execute
	struct s_Node		*right; // Right exec node to execute
}	t_Pipe_Node;

t_Node			*get_tail(t_Node *node);
void			free_tree(t_Node *node);

/**
 * Node for assigning variables into the current shell process
 * Not exported to children by default
**/
typedef struct s_Ass_Node
{
	enum e_Node_Type	type;
	struct s_Node		*left;
	struct s_Node		*right;
	t_entab				*table;
	char				*key; // variable identifier
	char				*value; // variable value
}	t_Ass_Node;

t_Node	*assignment_node(t_Parser *parser);

#endif

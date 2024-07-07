/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 21:06:03 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/05 17:04:08 by qang             ###   ########.fr       */
/*   Updated: 2024/06/28 19:01:38 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H
# include <sys/types.h>
//# include "a.h"
# include "libft.h"
# include "a.h"

typedef enum e_Node_Type
{
	Exec_Node = 1,
	Argument_Node,
	Redir_Node,
	Pipe_Node,
	AND_AND_NODE,
	OR_OR_NODE
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
void	exec_ast(t_Node *node);

/**
 * Node for executing commands
 */
typedef struct s_Exec_Node
{
	enum e_Node_Type	type;
	struct s_Node		*left;
	struct s_Node		*right;
	const char			*command; // Name of the command to execute
	int					arg_count; // Number of arguments in the command
	const char			**args; // Args of the cmd, first one being the cmdname
	t_entab				*table;
}	t_Exec_Node;

t_Exec_Node		*create_exec_node(const char *cmd_name, t_entab *envtab);
void			add_exec_arguments(t_Exec_Node *exec_node, const char *arg);

/**
 * Node for redirection
 */
typedef struct s_Redir_Node
{
	enum e_Node_Type	type;
	struct s_Node		*left;
	struct s_Node		*right;
	int					oldfd; // the fd to be replaced
	int					flags; // O_CREAT, O_APPEND etc
	mode_t				mode; // permission bits for READ WRITE EXECUTE
	const char			*file; // name of the file to open
	int					newfd; // fd of the file opened
}	t_Redir_Node;

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

#endif

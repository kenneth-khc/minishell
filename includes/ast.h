/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 21:06:03 by kecheong          #+#    #+#             */
/*   Updated: 2024/06/20 22:09:36 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

typedef enum e_Node_Type
{
	_,
	Exec_Node,
	Argument_Node,

}	t_Node_Type;

// typedef struct s_AST_Node
// {
// 	enum e_Node_Type	type;
// 	const char			*value;
// 	struct s_AST_Node	**children;
// 	int					children_count;
// }	t_AST_Node;
//
typedef struct s_Node
{
	enum e_Node_Type	type;
	struct s_Node		*left;
	struct s_Node		*right;
}	t_Node;

typedef struct s_Exec_Node
{
	enum e_Node_Type	type;
	struct s_Node		*left;
	struct s_Node		*right;
	const char			*command;
	int					arg_count;
	const char			**args;
	const char			**envp;
}	t_Exec_Node;

typedef struct s_Redir_Node
{
/* redir node
 * - filename
 * - mode
 * - fd
 */
}	t_Redir_Node;

typedef struct	s_Pipe_Node
{
/* pipe node
 * - left exec
 * - right exec
 */
}	t_Pipe_Node;

// t_AST_Node	*create_ast_node(enum e_Node_Type type);
// t_AST_Node	*create_child_node(t_AST_Node *parent, enum e_Node_Type type);
// void		print_children(t_AST_Node *parent);
t_Exec_Node	*create_exec_node(const char *cmd_name, const char **envp);
void		add_exec_arguments(t_Exec_Node *exec_node, const char *arg);

#endif

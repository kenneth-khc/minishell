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
# include <sys/types.h>

typedef enum e_Node_Type
{
	_,
	Exec_Node,
	Argument_Node,
	Redir_Node

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
	enum e_Node_Type	type;
	struct s_Node		*left;
	struct s_Node		*right;
	int					oldfd; // the fd to be replaced
	int					flags; // O_CREAT, O_APPEND etc
	mode_t				mode; // permission bits for READ WRITE EXECUTE
	const char			*file; // name of the file to open
	int					newfd; // fd of the file opened
}	t_Redir_Node;

typedef struct	s_Pipe_Node
{
/* pipe node
 * - left exec
 * - right exec
 */
}	t_Pipe_Node;

t_Exec_Node	*create_exec_node(const char *cmd_name, const char **envp);
void		add_exec_arguments(t_Exec_Node *exec_node, const char *arg);
t_Redir_Node	*create_redir_node(int oldfd, const char *filename, int flags, mode_t mode);
t_Node	*get_tail(t_Node *node);
void	print_nodes(t_Node *node);

#endif

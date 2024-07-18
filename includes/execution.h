/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 23:33:10 by qang              #+#    #+#             */
/*   Updated: 2024/07/17 19:11:14 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "tree.h"

void	exec_ast(t_Node *node);
void	exec(t_Exec_Node *node);
void	redir(t_Redir_Node *node);
void	subshell(t_Node *node);
void	ass_var(t_Ass_Node *node);

/*exec_ast_utils*/
void	execvepromax(char **args, t_entab *table, t_envar *path_node);
void	set_exit_status(int status);
int		exec_wait_pid(int last_pid);
int		get_exit_status(void);
int		forkpromax(void);
void	pipepromax(int fd[2]);
int		wait_for_child(int last_pid);
void	close_pipe(int fd[2]);

/*for redir*/
char	*expand_line(char *line, t_entab *table);
#endif
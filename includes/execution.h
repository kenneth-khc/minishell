/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 23:33:10 by qang              #+#    #+#             */
/*   Updated: 2024/07/20 12:11:47 by qang             ###   ########.fr       */
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
int		get_exit_status(void);
int		wait_for_child(int last_pid);
void	set_exit_status(int status);
void	execvepromax(char **args, t_entab *table, t_envar *path_node);
int		forkpromax(void);
int		ft_strcmp2(const char *s1, const char *s2);
int		openpromax(char *file, int flags, mode_t mode);
void	close_pipe(int fd[2]);
void	pipepromax(int fd[2]);

/*for redir*/
char	*expand_line(char *line, t_entab *table);
void	check_permissions(char *newfile, t_Direction direction);
#endif
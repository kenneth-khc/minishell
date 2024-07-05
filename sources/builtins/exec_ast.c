/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 22:15:03 by qang              #+#    #+#             */
/*   Updated: 2024/07/05 20:02:27 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"
#include <fcntl.h>

void	exec_ast(t_Node *node);

void	exec(t_Exec_Node *node)
{
	int	pid;

	pid = fork();
	
	printf("%d: %s ", pid, node->args[2]);
	fflush(stdout);
	if (pid < 0)
	{
		dprintf(STDERR_FILENO, "error");
		return ;
	}
	// if (pid > 0)
	// {
	// 	signal(SIGINT, SIG_IGN);
	// 	signal(SIGQUIT, SIG_IGN);
	// }
	if (ft_isbuiltin(node->args) && pid != 0)
		set_exit_status(run_builtin(node->args, node->table));
	else if (!ft_isbuiltin(node->args) && pid == 0)
	{
		execve((char *)node->args[0], (char **)node->args, NULL);
		execvepromax((char *)node->args[0], (char **)node->args, get_var("PATH", node->table));
		dprintf(STDERR_FILENO, "execve failed\n");
		exit(0);
	}
	else if (ft_isbuiltin(node->args) && pid == 0)
		exit(0);
	if (!ft_isbuiltin(node->args))
		set_exit_status(exec_wait_pid(pid, (char *)node->args[0]));
	// printf("exit_status: %d\n", get_exit_status());
}

void	pipepromax(int fd[2])
{
	int	err;

	err = pipe(fd);
	if (err == -1)
	{
		dprintf(STDERR_FILENO, "error");
		return ;
	}
}

int	forkpromax(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		dprintf(STDERR_FILENO, "error");
		return (-1);
	}
	return (pid);
}

void	paip(t_Pipe_Node *node)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	pipepromax(fd);
	pid1 = forkpromax();
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		exec_ast(node->left);
		exit(0);
	}
	pid2 = forkpromax();
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		exec_ast(node->right);
		exit(0);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void	redir(t_Redir_Node *node)
{
	int	pid1;

	pid1 = fork();
	if (pid1 == 0)
	{
		node->newfd = open(node->file, node->flags, node->mode);
		dup2(node->newfd, node->oldfd);
		close(node->newfd);
		exec_ast(node->left);
	}
	waitpid(pid1, NULL, 0);
}

// void	andand(t_andand *node)
// {
// 	exec_ast(node->left);
// 	if (get_exit_status() != 0)
// 		return ;
// 	else
// 		exec_ast(node->right);
// }
//
// void  oror(t_oror *node)
// {
// 	exec_ast(node->left);
// 	if (get_exit_status() == 0)
// 		return ;
// 	exec_ast(node->right);
// }

void	exec_ast(t_Node *node)
{
	if (node->type == Exec_Node)
		exec((t_Exec_Node *)node);
	else if (node->type == Redir_Node)
		redir((t_Redir_Node *)node);
	else if (node->type == Pipe_Node)
		paip((t_Pipe_Node *)node);
}

// int	main(int ac, char **av, char **env)
// {
// 	t_entab	*table = init_env_table(env);
// 	t_general	*general;

// 	t_exec *pwd;
// 	pwd = malloc(sizeof(t_exec));
// 	pwd->type = EXEC;
// 	pwd->left = 0;
// 	pwd->right = 0;
// 	pwd->args = &av[1];
// 	pwd->table = table;

// 	general = (t_general *) pwd;
// 	general->type = pwd->type;
// 	exec_ast(general);
// 	free_env(table);
// 	free(pwd);
// 	return (0);
// }

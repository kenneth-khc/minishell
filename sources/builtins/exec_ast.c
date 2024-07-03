/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 22:15:03 by qang              #+#    #+#             */
/*   Updated: 2024/07/02 20:37:12 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "a.h"

void	exec_ast(t_general *node);

void	exec(t_exec *node)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		dprintf(STDERR_FILENO, "error");
		return ;
	}
	if (ft_isbuiltin(node->args) && pid != 0)
		node->ret_status = run_builtin(node->args, node->table);
	else if (pid == 0)
	{
		execvepromax(node->args[0], node->args, get_var("PATH", node->table));
		dprintf(STDERR_FILENO, "execve failed\n");
	}
  set_exit_status(exec_wait_pid(pid, node->args[0]));
}

void	paip(t_pipe *node)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		dprintf(STDERR_FILENO, "error");
		return ;
	}
	int	pid1 = fork();
	if (pid1 < 0)
	{
		dprintf(STDERR_FILENO, "error");
		return ;
	}
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		exec_ast((t_general *)node->left);
		exit(0);
	}
	int	pid2 = fork();
	if (pid2 < 0)
	{
		dprintf(STDERR_FILENO, "error");
		return ;
	}
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		// close(fd[0]);
		// close(fd[1]);
		exec_ast((t_general *)node->right);
		exit(0);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void	redir(t_Redir_Node *node)
{
	int	pid1 = fork();

	if (pid1 < 0)
	{
		printf("error");
		return ;
	}
	if (pid1 == 0)
	{
		if (node->args[1][0] == '<')
		{
			node->newfd = open(node->args[2], node->flags);
			dup2(node->newfd, node->oldfd);
			close(node->newfd);
			exec_ast(node->left);
		}
		else if (node->args[1][0] == '>')
		{
			node->newfd = open(node->args[2], node->flags);
			dup2(node->newfd, node->oldfd);
			close(node->newfd);
			exec_ast(node->left);
		}
	}
	waitpid(pid1, NULL, 0);
}

// void	andand(t_andand *node)
// {
// 	exec_ast(node->left);
// 	if ()
// }

void	exec_ast(t_general *node)
{
	if (node->type == EXEC)
		exec((t_exec *)node);
	else if (node->type == REDIR)
		redir((t_Redir_Node *)node);
	else if (node->type == PIPE)
		paip((t_pipe *)node);
	else if (node->type == BACK)
		return ;
	else if (node->type == LIST)
		return ;
}

int	main(int ac, char **av, char **env)
{
	t_entab	*table = init_env_table(env);
	t_general	*general;

  char **args;
  args = malloc(sizeof(char *) * 2);
  args[0] = ft_strdup("pwd");
  args[1] = 0;
  t_exec *pwd;
  pwd = malloc(sizeof(t_exec));
  pwd->type = EXEC;
  pwd->left = 0;
  pwd->right = 0;
  pwd->args = args;
  pwd->table = table;

  general = (t_general *) pwd;
  general->type = pwd->type;
  exec_ast(general);
  free(args[0]);
  free(args);
  free_env(table);
  free(pwd); 
  
	// t_exec	*ls_la;
	// ls_la = malloc(sizeof(t_exec));
	// ls_la->type = EXEC;
	// ls_la->args = (char *[]){"ls", "-la", NULL};
	// ls_la->left = NULL;
	// ls_la->right = NULL;
	// ls_la->table = table;

	// t_exec	*grep_exec;
	// grep_exec = malloc(sizeof(t_exec));
	// grep_exec->type = EXEC;
	// grep_exec->args = (char *[]){"grep", "exec", NULL};
	// grep_exec->left = NULL;
	// grep_exec->right = NULL;
	// grep_exec->table = table;

	// t_exec	*wc;
	// wc = malloc(sizeof(t_exec));
	// wc->type = EXEC;
	// wc->args = (char *[]){"wc", NULL};
	// wc->left = NULL;
	// wc->right = NULL;
	// wc->table = table;

	// t_exec	*bro;
	// bro = malloc(sizeof(t_exec));
	// bro->type = EXEC;
	// bro->args = (char *[]){"/Users/qang/42/minishell/sources/builtins/bro", NULL};
	// bro->left = NULL;
	// bro->right = NULL;
	// bro->table = table;

	// t_pipe	*pip1 = malloc(sizeof(t_pipe));
	// pip1->type = PIPE;
	// pip1->args = (char *[]){"ls -la", "|", "grep exec", NULL};

	// t_general	*general1 = (t_general *) ls_la;
	// general1->type = ls_la->type;
	// pip1->left = general1;

	// t_general	*general2 = (t_general *) grep_exec;
	// general2->type = grep_exec->type;
	// pip1->right = general2;

	// t_pipe	*pip2 = malloc(sizeof(t_pipe));
	// pip2->type = PIPE;
	// pip2->args = (char *[]){"ls -la", "|", "grep exec", "|", "./bro", NULL};

	// general = (t_general *) bro;
	// general->type = bro->type;
	// pip2->right = general;

	// general = (t_general *) pip1;
	// general->type = pip1->type;
	// pip2->left = general;

	// t_pipe	*pip3 = malloc(sizeof(t_pipe));
	// pip3->type = PIPE;
	// pip3->args = (char *[]){"ls -la", "|", "grep exec", "|", "/Users/qang/42/minishell/sources/builtins/bro", "|", "wc", NULL};

	// general = (t_general *) pip2;
	// general->type = pip2->type;
	// pip3->left = general;

	// general = (t_general *) wc;
	// general->type = wc->type;
	// pip3->right = general;

	// general = (t_general *) pip3;
	// general->type = pip3->type;

	// general = (t_general *) pip1;
	// general->type = pip1->type;
	
	// exec_ast(general);
	return (0);
}

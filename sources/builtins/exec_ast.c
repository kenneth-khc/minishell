#include "a.h"

void	exec_ast(t_general *node);

void	exec(t_exec *node)
{
	execve(node->args[0], node->args, NULL);
	printf("execve failed\n");
}

void	paip(t_pipe *node)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		printf("error");
		return ;
	}
	int	pid1 = fork();
	if (pid1 < 0)
	{
		printf("error");
		return ;
	}
	if (pid1 == 0)
	{
		close(STDOUT_FILENO);
		// dup(fd[1]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		exec_ast((t_general *)node->left);
	}
	int	pid2 = fork();
	if (pid2 < 0)
	{
		printf("error");
		return ;
	}
	if (pid2 == 0)
	{
		close(STDIN_FILENO);
		// dup(fd[0]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		exec_ast((t_general *)node->right);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void	redir(t_redir *node)
{
	int	pid1 = fork();

	if (pid1 < 0)
	{
		printf("error");
		return ;
	}
	printf("hello from %d\n", pid1);
	if (pid1 == 0)
	{
		if (node->args[1][0] == '<')
		{
			int	fd = open(node->args[2], O_RDONLY);
			dup2(fd, STDIN_FILENO);
			close(fd);
			exec_ast(node->left);
		}
		else if (node->args[1][0] == '>')
		{
			int	fd = open(node->args[2], O_WRONLY);
			dup2(fd, STDOUT_FILENO);
			close(fd);
			exec_ast(node->left);
		}
	}
	waitpid(pid1, NULL, 0);
}

void	exec_ast(t_general *node)
{
	if (node->type == EXEC) 
		exec((t_exec *)node);
	else if (node->type == REDIR)
		redir((t_redir *)node);
	else if (node->type == PIPE)
		paip((t_pipe *)node);
	else if (node->type == BACK)
		return ;
	else if (node->type == LIST)
		return ;
}

int	main(int ac, char **av, char **env)
{
	t_redir	*redir_node;
	t_exec	*ast;
	t_general	*general;

	ast = malloc(sizeof(t_exec));
	ast->type = EXEC;
	ast->args = (char *[]){"/bin/ls", "-la", NULL};
	ast->left = NULL;
	ast->right = NULL;

	redir_node = malloc(sizeof(t_redir));
	redir_node->type = REDIR;
	redir_node->args = (char *[]){"0", ">", "/Users/qang/42/minishell/sources/builtins/a", NULL};
	general = (t_general *) ast;
	general->type = ast->type;
	redir_node->left = general;
	redir_node->right = NULL;
	general = (t_general *) redir_node;
	general->type = redir_node->type;

	t_exec *temp;
	temp = malloc(sizeof(t_exec));
	temp->type = EXEC;
	temp->args = (char *[]){"/usr/bin/grep", "test", NULL};
	temp->left = NULL;
	temp->right = NULL;

	t_pipe	*pipe_node = malloc(sizeof(t_pipe));
	pipe_node->type = PIPE;
	pipe_node->args = (char *[]){"/bin/ls -la", "|", "/usr/bin/grep", "test", NULL};

	t_general	*general1 = (t_general *) ast;
	general1->type = ast->type;
	pipe_node->left = general1;

	t_general	*general2 = (t_general *) temp;
	general2->type = temp->type;
	pipe_node->right = general2;

	t_pipe	*pip = malloc(sizeof(t_pipe));
	pip->type = PIPE;
	pip->args = (char *[]){"/usr/bin/grep", "|", "/usr/bin/wc", NULL};
	general = (t_general *) pipe_node;
	general->type = pipe_node->type;
	pip->left = general;

	t_exec *temp1;
	temp1 = malloc(sizeof(t_exec));
	temp1->type = EXEC;
	temp1->args = (char *[]){"/usr/bin/wc", NULL};
	temp1->left = NULL;
	temp1->right = NULL;

	general = (t_general *) temp1;
	general->type = temp1->type;
	pip->right = general;

	general = (t_general *)pip;
	general->type = pip->type;

	exec_ast(general);
	return (0);
}
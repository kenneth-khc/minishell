#include "a.h"
#include <limits.h>

int	echo(char **args)
{
	int	newline;
	int	i;
	
	newline = 10;
	i = 1;
	if (length(args) == 1)
		return (printf("\n"));
	else
	{
		while (args[i] && ft_strcmp(args[i], "-n") == 0)
		{
			i++;
			newline = 0;
		}
		while (args[i])
		{
			printf("%s", args[i]);
			if (args[i + 1])
				printf(" ");
			i++;	
		}
		if (newline)
			printf("%c", newline);
	}
	return (0);
}

int	cd(char **args, t_entab *table)
{
	int		errno;

	errno = 0;
	if (length(args) == 1)
	{
		if (get_var("HOME", table) == NULL)
			return (0);
		errno = chdir(get_var("HOME", table)->val);
	}
	else if (length(args) == 2)
	{
		if (ft_strlen(args[1]) > 255)
			return (printf("cd: %s: File name too long\n", args[1]));
		errno = chdir(args[1]);
	}
	else
		printf("cd: too many arguments\n"); 
	if (errno)
		printf("cd: %s: No such file or directory\n", args[1]);
	/*if (errno)
		printf("cd: %s: %s\n", args[1], strerror(errno));*/
	return (0);
}

int	pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX - 1))
		return (printf("%s\n", cwd));
	return (1);
}

int	export(char **args, t_entab *table)
{
	int	i;

	i = 1;
	if (length(args) == 1)
		print_sorted_env(table);
	else
		while (args[i])
		{
			if (args[i][0] && args[i][0] == '=')
				return (printf("export: `%s': not a valid identifier\n", args[i]));
			else
				add_var(args[i], table);
			i++;
		}
	return (0);
}

int	unset(char **args, t_entab *table)
{
	int	i;

	i = 1;
	while (args[i])
		del_var(args[i++], table);
	return (0);
}

int	print_env(char **args, t_entab *table)
{
	t_envar	*node;
	t_envar	*absfn;

	node = table->head;
	while (node)
	{
		if (ft_strcmp(node->key, "_") == 0)
		{
			absfn = node;
			node = node->next;
			continue ;
		}
		if (node->val != NULL)
			printf("%s=%s\n", node->key, node->val);
		node = node->next;
	}
	printf("%s=%s\n", absfn->key, absfn->val);
	return (0);
}

int	ft_atoipro(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\t' || str[i] == '\r')
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
		if (!ft_isdigit(str[i++]))
		{
			printf("exit: %s: numeric argument required\n", str);
			return (0);
		}
	return (ft_atoi(&str[i]));
}

int	exit_sh(char **arg, t_entab *table)
{
	int	i;

	i = 0;
	printf("exit\n");
	if (length(arg) == 1)
	{
		free_env(table);
		exit(0);
	}
	if (length(arg) == 2)
		ft_atoipro(arg[1]);
	else
		printf("exit: too many arguments\n");
	return (0);
}

int	main(int ac, char **av, char **env)
{
	if (ac > 1)
	{
		t_entab	*table;

		table = init_env_table(env);
		if (ft_strcmp("echo", av[1]) == 0)
			echo(&av[1]);
		else if (ft_strcmp("cd", av[1]) == 0)
			cd(&av[1], table);
		else if (ft_strcmp("pwd", av[1]) == 0)
			pwd();
		else if (ft_strcmp("export", av[1]) == 0)
			export(&av[1], table);
		else if (ft_strcmp("unset", av[1]) == 0)
			unset(&av[1], table);
		else if (ft_strcmp("env", av[1]) == 0)
			print_env(&av[1], table);
		else if (ft_strcmp("exit", av[1]) == 0)
			exit_sh(&av[1], table);
	}
	return (0);
}

#ifndef A_H
# define A_H

#include "libft/libft.h"
/*envar = env variable*/
typedef struct s_envar
{
	char			*key;
	char			*val;
	struct s_envar	*prev;
	struct s_envar	*next;
}	t_envar;

typedef struct s_entab
{
	int				size;
	t_envar			*head;
	t_envar			*tail;
}	t_entab;

int	ft_strcmp(char *s1, char *s2);
t_envar	*print_sorted_env(t_entab *table);
int	length(char **arg);
void	add_var(char *str, t_entab *table);
void	del_var(char *key, t_entab *table);
t_envar	*get_var(char *key, t_entab *table);
t_entab	*init_env_table(char **env);
void	free_env(t_entab *table);

typedef enum e_types
{
	EXEC,
	REDIR,
	PIPE,
	LIST,
	BACK
}	t_type;

typedef struct s_general
{
	t_type	type;
}	t_general;

typedef struct s_exec
{
	t_type	type;
	char	**args;
	t_general	*left;
	t_general	*right;
}	t_exec;

typedef struct s_pipe
{
	t_type	type;
	char	**args;
	t_general	*left;
	t_general	*right;
}	t_pipe;

typedef struct s_redir
{
	t_type	type;
	char	**args;
	t_general	*left;
	t_general	*right;
}	t_redir;

typedef struct s_temp
{
	t_type	type;
	char	**args;
	t_general	*left;
	t_general	*right;
}	t_temp;

typedef struct s_back
{
	t_type	type;
	char	**args;
	t_general	*left;
	t_general	*right;
}	t_back;
#endif

#ifndef A_H
# define A_H

#include "libft/libft.h"
#include <stdbool.h>
/*envar = env variable*/
typedef struct s_envar
{
	char						*key;
	char						*val;
	bool						display;
	struct s_envar	*prev;
	struct s_envar	*next;
}	t_envar;

typedef struct s_entab
{
	int					size;
	t_envar			*head;
	t_envar			*tail;
}	t_entab;

/*use the one in libft later*/
int			ft_strcmp(char *s1, char *s2);

/*prints sorted env (for export)*/
t_envar	*print_sorted_env(t_entab *table);

/*get length of args*/
int			length(char **arg);

/*env functions*/
void		add_var(char *str, t_entab *table);
void		del_var(char *key, t_entab *table);
t_envar	*get_var(char *key, t_entab *table);
t_entab	*init_env_table(char **env);
void		free_env(t_entab *table);

int	cd(char **args, t_entab *table);
void	update_pwd(char **args, t_entab *table);

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
	int		ret_status;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a.h                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 22:27:01 by qang              #+#    #+#             */
/*   Updated: 2024/07/03 16:30:16 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef A_H
# define A_H

# include "libft/libft.h"
# include <stdbool.h>
# include <limits.h>
/*envar = env variable*/
typedef struct s_envar
{
	char			*key;
	char			*val;
	bool			display;
	struct s_envar	*prev;
	struct s_envar	*next;
}	t_envar;

typedef struct s_entab
{
	int				size;
	t_envar			*head;
	t_envar			*tail;
}	t_entab;

/*use the one in libft later*/
int			ft_strcmp(char *s1, char *s2);

/*prints sorted env (for export)*/
t_envar		*print_sorted_env(t_entab *table);

/*get length of args*/
int			length(char **arg);

/*env functions*/
void		add_var(char *str, t_entab *table);
void		del_var(char *key, t_entab *table);
t_envar		*get_var(char *key, t_entab *table);
t_entab		*init_env_table(char **env);
void		free_env(t_entab *table);
t_envar		*copy_env(t_envar *src);

/*builtin funcs*/
int			cd(char **args, t_entab *table);
void		update_pwd(char **args, t_entab *table);
int			echo(char **args);
int			print_env(char **args, t_entab *table);
int			exit_sh(char **arg, t_entab *table);
int			export(char **args, t_entab *table);
int			pwd(char **args, t_entab *table);
int			unset(char **args, t_entab *table);

bool		ft_isbuiltin(char **av);
int			run_builtin(char **av, t_entab *table);

int			execvepromax(char *file, char **args, t_envar *path_node);
void		set_exit_status(int status);
int			exec_wait_pid(int pid, char *name);
int			get_exit_status(void);

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
	t_type		type;
	t_general	*left;
	t_general	*right;
	t_entab		*table;
	char		**args;
	int			ret_status;
}	t_exec;

typedef struct s_pipe
{
	t_type		type;
	char		**args;
	t_general	*left;
	t_general	*right;
}	t_pipe;

typedef struct s_redir
{
	t_type		type;
	char		**args;
	int				oldfd;
	int				newfd;
	int				flags;
	mode_t		mode;
	t_general	*left;
	t_general	*right;
}	t_Redir_Node;

typedef struct s_temp
{
	t_type		type;
	char		**args;
	t_general	*left;
	t_general	*right;
}	t_temp;

typedef struct s_back
{
	t_type		type;
	char		**args;
	t_general	*left;
	t_general	*right;
}	t_back;

typedef struct s_andand
{
	t_type		type;
	char		**args;
	t_general	*left;
	t_general	*right;
}	t_andand;

typedef struct s_oror
{
	t_type		type;
	char		**args;
	t_general	*left;
	t_general	*right;
}	t_oror;
#endif

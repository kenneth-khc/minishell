/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a.h                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 22:27:01 by qang              #+#    #+#             */
/*   Updated: 2024/07/12 18:15:22 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef A_H
# define A_H

# include <stdbool.h>
# include <unistd.h>
# include "libft.h"
# include <stdio.h>
# ifndef SHELL
#  define SHELL "bish"
# endif

# define EXPORT 0b1
# define LOCAL 0b10
# define DISPLAY 0b100
/*envar = env variable*/
typedef struct s_envar
{
	char			*key;
	char			*val;
	int       state;
	char			*pwd;
	struct s_envar	*prev;
	struct s_envar	*next;
}	t_envar;

typedef struct s_entab
{
	int				size;
	t_envar			*head;
	t_envar			*tail;
}	t_entab;

/*signal handling*/
void	init_signal(void);
void	ignore_sigs(void);
void	set_sig(void);

/*prints sorted env (for export)*/
int			print_sorted_env(t_entab *table);
t_envar		*copy_and_sort_env(t_entab *table);
void		print_and_free_env(t_envar *chead);

/*get length of args*/
int			length(char **arg);

/*env functions*/
void		add_var(char *str, t_entab *table);
void		del_var(char *key, t_entab *table);
t_envar		*get_var(char *key, t_entab *table);
t_entab		*init_env_table(char **env);
void		free_env(t_entab *table);
t_envar		*copy_env(t_envar *src);
char		**env_convert(t_entab *table);
void			incr_shlvl(t_entab *table);
void  	special_pwd(t_envar *node, t_envar *new);
t_envar		*new_env_var(const char *str);
void		free_env_list(t_envar *node);

/*builtin funcs*/
int			cd(char **args, t_entab *table);
void	  add_pwd(t_entab *table);
void	  update_oldpwd(char *oldpwd, t_entab *table);
void		update_pwd(char **args, t_entab *table);
int			echo(char **args);
int			print_env(char **args, t_entab *table);
int			exit_sh(char **arg, t_entab *table);
int			export(char **args, t_entab *table);
int			pwd(char **args, t_entab *table);
int			unset(char **args, t_entab *table);

bool    ft_isbuiltin(const char *command);
int			run_builtin(const char **av, t_entab *table);

/*exec_ast_utils*/
void		execvepromax(char **args, t_entab *table, t_envar *path_node);
void		set_exit_status(int status);
int	    exec_wait_pid(int last_pid);
int			get_exit_status(void);
int     forkpromax(void);
void    pipepromax(int fd[2]);
int			wait_for_child(int last_pid);
void		close_pipe(int fd[2]);

void		*mallocpromax(size_t size);
#endif

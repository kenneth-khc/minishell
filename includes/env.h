/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 22:27:01 by qang              #+#    #+#             */
/*   Updated: 2024/08/05 20:08:22 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stdlib.h>

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
	int				state;
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
void	default_sigs(void);

/*prints sorted env (for export)*/
int		print_sorted_env(t_entab *table);
t_envar	*copy_and_sort_env(t_entab *table);
void	print_and_free_env(t_envar *chead);

/*get length of args*/
int		length(char **arg);

/*env functions*/
void	add_var(char *str, t_entab *table);
void	del_var(char *key, t_entab *table);
t_envar	*get_var(char *key, t_entab *table);
t_entab	*init_env_table(char **env);
void	free_env(t_entab *table);
t_envar	*copy_env(t_envar *src);
t_envar	*new_env_var(const char *str);
void	free_env_list(t_envar *node);
char	**env_convert(t_entab *table);
void	add_ass(char *str, t_entab *table);
void	incr_shlvl(t_entab *table);

void	*mallocpromax(size_t size);
#endif

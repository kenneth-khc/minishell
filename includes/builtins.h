/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 23:46:25 by qang              #+#    #+#             */
/*   Updated: 2024/07/17 00:57:19 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "env.h"
# include <stdbool.h>

/*builtin funcs*/
int			cd(char **args, t_entab *table);
void		add_pwd(t_entab *table);
void		update_oldpwd(char *oldpwd, t_entab *table);
void		update_pwd(char **args, t_entab *table);
int			echo(char **args);
int			print_env(char **args, t_entab *table);
int			exit_sh(char **arg, t_entab *table);
int			ft_export(char **args, t_entab *table);
int			pwd(char **args, t_entab *table);
int			unset(char **args, t_entab *table);

bool		ft_isbuiltin(const char *command);
int			run_builtin(const char **av, t_entab *table);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_funcs3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 00:11:02 by qang              #+#    #+#             */
/*   Updated: 2024/07/07 00:13:23 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "a.h"

void	incr_shlvl(t_entab *table)
{
	t_envar	*shlvl;
	int		lvl;

	shlvl = get_var("SHLVL", table);
	if (shlvl)
	{
		lvl = ft_atoi(shlvl->val);
		lvl++;
		free(shlvl->val);
		shlvl->val = ft_itoa(lvl);
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:15:19 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/18 21:09:52 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"
#include "env.h"

char	*copy_var_val(char *key, t_entab *env)
{
	t_envar	*envar;
	char	*value;

	envar = get_var(key, env);
	if (envar && (envar->state & DISPLAY))
		value = envar->val;
	else
		value = NULL;
	if (value)
		value = ft_strdup(value);
	return (value);
}

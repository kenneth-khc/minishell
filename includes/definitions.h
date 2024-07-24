/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:17:25 by kecheong          #+#    #+#             */
/*   Updated: 2024/07/21 18:05:39 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINITIONS_H
# define DEFINITIONS_H

# include <stdbool.h>

bool	is_blank(const char c);
bool	is_metacharacter(const char c);
bool	is_control_operator(const char *str);
bool	is_redirection_operator(const char *str);
bool	is_operator(const char *str);
bool	is_valid_name(const char *start, const char *end);
bool	is_not_identifier(char c);
bool	is_quote(char c);
bool	is_dollar(char c);

#endif

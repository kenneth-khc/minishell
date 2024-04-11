/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:25:32 by kecheong          #+#    #+#             */
/*   Updated: 2024/04/11 10:48:00 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

enum e_Tokens {
	WORD = 256,
	PIPE,
	AND_AND,
	OR_OR,
	INPUT_REDIR,
	HERE_DOC,
	OUTPUT_REDIR,
	OUTPUT_APPEND,
	STAR
};

typedef struct s_Token {
	struct s_Token	*next;
	int				type;
	const char		*lexeme;
	int	num;
} t_Token;

typedef struct s_Token_list {
	struct s_Token	*head;
	struct s_Token	*tail;
} t_Token_list;

#endif
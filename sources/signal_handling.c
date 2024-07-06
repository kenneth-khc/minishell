/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 22:09:08 by qang              #+#    #+#             */
/*   Updated: 2024/07/06 23:52:38 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void	signal_print_newline(int sig)
{
	(void)sig;
	rl_on_new_line();
}

void	set_sig(void)
{
	struct sigaction	sa;

	sa.sa_handler = &signal_print_newline;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	ignore_sigs(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

static void	re_prompt(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	init_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = re_prompt;
	sigaction(SIGINT, &sa, NULL);
}

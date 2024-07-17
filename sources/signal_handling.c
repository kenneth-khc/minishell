/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 22:09:08 by qang              #+#    #+#             */
/*   Updated: 2024/07/17 01:20:37 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

void	set_sig(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
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
// todo: fix readline linking
//	rl_replace_line("", 0);
	rl_redisplay();
}

void	init_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = re_prompt;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:45:23 by dcyprien          #+#    #+#             */
/*   Updated: 2022/05/05 23:42:27 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// CTRL + C = SIGINT / interrupt -> SIGNUM = 2
// CTRL + \ = Does nothing 
// CTRL + D = SIGQUIT / Quit the shell

void	sighandler(int signum)
{
	struct termios	termios_old;
	struct termios	termios_new;

	if (signum == SIGQUIT)
	{
		g_exit_code = 131;
		ft_putstr_fd("\b\b  \b\b", 1);
		tcgetattr(0, &termios_new);
		tcgetattr(0, &termios_old);
		termios_new.c_lflag &= ~(ISIG | ECHOCTL);
		tcsetattr(0, 0, &termios_new);
		tcsetattr(0, 0, &termios_old);
	}
	if (signum == SIGINT)
	{
		g_exit_code = 130;
		ft_show_prompt();
	}
}

void	set_sigaction(int sigh)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	sigemptyset(&act.sa_mask);
	if (!sigh)
		act.sa_handler = sighandler;
	else if (sigh == 1)
		act.sa_handler = sigign;
	else
		act.sa_handler = sig_heredoc;
	sigaction(SIGQUIT, &act, NULL);
	sigaction(SIGINT, &act, NULL);
}

void	ft_show_prompt(void)
{
	ft_putstr_fd("\b \b\b \b\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	inthandler2(int sig)
{
	(void)sig;
	g_exit_code = 130;
	exit(g_exit_code);
}

void	sig_quit(int signum)
{
	(void)signum;
	ft_putstr_fd("exit\n", 1);
	exit(g_exit_code);
}

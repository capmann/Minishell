/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:45:23 by dcyprien          #+#    #+#             */
/*   Updated: 2022/04/13 16:32:41 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// CTRL + C = SIGINT / interrupt -> SIGNUM = 2
// CTRL + \ = Does nothing 
// CTRL + D = SIGQUIT / Quit the shell

void	sighandler(int signum)
{
	struct termios	termios_old;
	struct termios	termios_new;

	if (signum == SIGQUIT)
	{
		ft_putstr_fd("\b\b  \b\b", 1);
		tcgetattr(0, &termios_new);
		tcgetattr(0, &termios_old);
		termios_new.c_lflag &= ~(ISIG | ECHOCTL);
		tcsetattr(0, 0, &termios_new);
		tcsetattr(0, 0, &termios_old);
	}
	if (signum == SIGINT)
	{
		ft_show_prompt();
	}
}

void	set_sigaction(struct sigaction act)
{
	sigemptyset(&act.sa_mask);
	act.sa_handler = sighandler;
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

void	sig_backslash(int signum)
{
	(void)signum;
	ft_show_prompt();
}

void	sig_quit(int signum)
{
	(void)signum;
	exit(0);
}

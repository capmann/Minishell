/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 20:01:08 by cmarteau          #+#    #+#             */
/*   Updated: 2022/05/05 22:53:47 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sigign(int signum)
{
	(void)signum;
	if (signum == SIGINT)
	{
		g_exit_code = 130;
		ft_putstr_fd("\n", 1);
	}
	if (signum == SIGQUIT)
	{
		g_exit_code = 131;
		ft_putstr_fd("Quit (core dumped)\n", 1);
	}
}

void	disable_signals(int fork)
{
	if (fork == 0)
	{
		set_sigaction(0);
	}
	else
	{
		set_sigaction(1);
	}
}

void	signals_heredoc(int fork)
{
	if (fork == 0)
	{
		set_sigaction(3);
	}
	else
	{
		set_sigaction(1);
	}
}

void	sig_heredoc(int signum)
{
	(void)signum;
	if (signum == SIGINT)
	{
		g_exit_code = 130;
		exit(g_exit_code);
	}
}

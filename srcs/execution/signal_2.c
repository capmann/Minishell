/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarteau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 20:01:08 by cmarteau          #+#    #+#             */
/*   Updated: 2022/05/03 20:01:11 by cmarteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sigign(int signum)
{
	(void)signum;
	if (signum == SIGINT)
		ft_putstr_fd("\n", 1);
}

void	disable_signals(int fork)
{
	if (fork == 0)
	{
		set_sigaction(1);
	}
	else
	{
		set_sigaction(2);
	}
}

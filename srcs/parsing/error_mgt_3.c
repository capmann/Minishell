/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mgt_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 23:33:57 by dcyprien          #+#    #+#             */
/*   Updated: 2022/05/07 01:47:44 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	null_redir(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if ((cmd[i] == '<' || cmd[i] == '>')
			&& char_in_quote(cmd, cmd[i], i) == 0)
			while (cmd[i] && !ft_isalpha(cmd[i]))
				i++;
		if (cmd[i] && (cmd[i] == '>' || cmd[i] == '<')
			&& char_in_quote(cmd, cmd[i], i) == 0)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:22:05 by dcyprien          #+#    #+#             */
/*   Updated: 2022/04/26 19:25:07 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_in_quote(char *cmd, char c, int index)
{
	int	i;
	int	quote;
	int	pos;
	int	*tab;

	if (is_quote(c) == EXIT_FAILURE)
		return (char_in_quote(cmd, c, index));
	pos = quote_pos(cmd, c, 0, 0);
	if (pos == 1 || pos == quote_pos(cmd, c, 1, 0))
		return (EXIT_SUCCESS);
	tab = parsing_quotes(cmd);
	if (!tab)
		return (EXIT_SUCCESS);
	i = -1;
	while (tab[++i])
	{
		quote = is_closed_quotes(cmd, i);
		if (tab[i] != c && i < pos && quote > 1)
		{
			secure_free((void **)&tab);
			return (quote);
		}
	}
	secure_free((void **)&tab);
	return (EXIT_SUCCESS);
}

int	*parsing_quotes(char *s)
{
	int	j;
	int	k;
	int	*tab;

	j = -1;
	k = -1;
	if (!s || count_quotes(s) == 0)
		return (NULL);
	tab = malloc(sizeof(int) * (count_quotes(s) + 1));
	while (s[++j])
		if (s[j] == 34 || s[j] == 39)
			tab[++k] = s[j];
	tab[k] = 0;
	return (tab);
}

int	count_quotes(char *s)
{	
	int	j;
	int	k;

	j = -1;
	k = 0;
	while (s[++j])
		if (s[j] == 34 || s[j] == 39)
			k++;
	return (k);
}

int	verify_cmd(char *cmd)
{
	int	i;

	i = 0;
	if (ft_strlen(cmd) == 0)
		return (EXIT_FAILURE);
	while (cmd[i])
	{
		if (cmd[i] == ' ' || cmd[i] == 9)
			i++;
		else
			return (EXIT_SUCCESS);
	}
	if (!cmd[i])
		return (2);
	return (EXIT_SUCCESS);
}

int	null_pipe(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '|')
		{
			while (cmd[i] && !ft_isalnum(cmd[i]))
				i++;
			if (!cmd[i])
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

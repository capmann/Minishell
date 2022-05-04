/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 21:10:29 by cmarteau          #+#    #+#             */
/*   Updated: 2022/04/28 16:23:48 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	quotes_skip(t_list *list)
{
	t_data	*data;
	int		i;

	data = list->prems;
	i = 0;
	while (data)
	{
		i = 0;
		while (++i < data->nb_args)
			skip_quotes(data, i);
		data = data->next;
	}
}

void	ignore_redirect(t_list *list)
{
	t_data	*data;
	int		i;
	t_data	*tmp;

	tmp = NULL;
	data = list->prems;
	while (data)
	{
		i = -1;
		while (data->cmd && data->cmd[++i])
		{
			if (data->cmd[i][0] == '>' || data->cmd[i][0] == '<')
			{
				secure_free((void **)&data->cmd[i]);
				while (data->cmd[++i])
				{
					data->cmd[i - 1] = ft_strdup(data->cmd[i]);
					secure_free((void **)&data->cmd[i]);
				}
				i = -1;
			}
		}
		data = data->next;
	}
}

int	quote_pos(char *cmd, char c, int index)
{
	int	i;
	int	k;

	i = -1;
	k = 0;
	while (cmd[++i] && i <= index)
	{
		if (is_quote(cmd[i]) == EXIT_SUCCESS)
			k++;
		if (cmd[i] == c && i == index)
			break ;
	}
	return (k);
}

int	char_in_quote(char *cmd, char c, int index)
{
	int	i;
	int	quote;

	i = -1;
	while (cmd[++i] && i <= index)
	{
		quote = is_closed_quotes(cmd, i);
		if (is_quote(cmd[i]) == EXIT_SUCCESS
			&& quote > 1)
		{
			i++;
			while (cmd[i] && cmd[i] != quote)
			{
				if (cmd[i] == c)
					return (quote);
				i++;
			}
		}
	}
	return (0);
}

int	cmd_digit(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (EXIT_FAILURE);
	while (cmd[i])
	{
		if (ft_isalpha(cmd[i]) || ft_isdigit(cmd[i]))
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

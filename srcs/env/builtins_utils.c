/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:07:01 by dcyprien          #+#    #+#             */
/*   Updated: 2022/04/28 16:12:53 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_echo(char *cmd)
{
	int	k;

	k = 0;
	while (cmd && cmd[k])
	{
		ft_putchar_fd(cmd[k], 1);
		if (cmd[k])
			k++;
	}
}

char	*skip_spaces(char *cmd)
{
	int		i;
	int		k;
	char	*str;

	i = 0;
	k = -1;
	if (!cmd)
		return (NULL);
	str = ft_strdup(cmd);
	while (cmd[i])
	{
		while (cmd[i] && cmd[i] == ' ')
			i++;
		while (cmd[i] && cmd[i] != ' ')
			str[++k] = cmd[i++];
		if (cmd[i] && cmd[i] == ' ')
			str[++k] = cmd[i++];
	}
	while (k >= 0 && str[k] == ' ')
		str[k--] = 0;
	str[++k] = '\0';
	secure_free((void *)&cmd);
	return (str);
}

int	file_test(char *tmp, int i, int k)
{
	while (tmp[i] != ' ' && tmp[i])
		i++;
	if (test_file(tmp, i, k) == -1)
	{
		secure_free((void **)&tmp);
		return (-1);
	}
	return (i - k + 2);
}

char	*access_path(char **tmp_path, char *tmp, t_data *data)
{
	int	i;

	i = -1;
	while (tmp_path && tmp_path[++i])
	{
		tmp = ft_strcat(tmp_path[i], data->cmd[0]);
		if (tmp && access(tmp, F_OK) == 0 && access(tmp, X_OK) == 0)
		{
			data->path = ft_strdup(tmp);
			free_malloc(tmp_path, tmp, 2);
			return (data->path);
		}
		secure_free((void **)&tmp);
	}
	free_malloc(tmp_path, data->cmd[0], 1);
	return (NULL);
}

int	check_quote(char *tab, int pos, char c)
{
	int	i;
	int	j;
	int	quote;

	i = -1;
	while (tab[++i] && i < (pos - 1))
	{
		j = i + 1;
		quote = is_closed_quotes(tab, i);
		if (quote > 1)
			while (tab[j] && tab[j] != quote)
				j++;
		if (tab[i] != c && quote > 1 && j > (pos - 1))
		{
			secure_free((void **)&tab);
			return (quote);
		}
		i = j;
	}
	secure_free((void **)&tab);
	return (EXIT_SUCCESS);
}

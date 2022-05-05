/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:50:56 by dcyprien          #+#    #+#             */
/*   Updated: 2022/05/05 19:28:03 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_data	*fill_data(char *cmd, t_data *data, char **tab)
{
	int	i;

	i = 0;
	data->cmd = tab;
	while (data->cmd && data->cmd[i])
		i++;
	data->nb_args = i;
	data->redirect = get_redirect(cmd, data);
	return (data);
}

void	free_malloc(char **cmd, char *path, int mode)
{
	int	i;

	i = -1;
	if (mode == 1)
	{
		if (cmd && !cmd[0] && cmd[1])
		{
			secure_free((void **)&cmd[0]);
			i = 0;
		}
		while (cmd && cmd[++i])
			secure_free((void **)&cmd[i]);
		secure_free((void **)&cmd);
	}
	if (mode == 2)
	{
		while (cmd[++i])
			secure_free((void **)&cmd[i]);
		secure_free((void **)&cmd);
		secure_free((void **)&path);
	}
	if (mode == 3)
		secure_free((void **)&path);
}

char	**get_command(char *cmd, t_data *data)
{
	char	**tab;
	int		i;

	i = skip_redirect(cmd);
	tab = ft_split(cmd, ' ', i, 0);
	i = 0;
	while (tab && tab[i])
	{
		tab[i] = clear_tab(tab[i]);
		i++;
	}
	data = fill_data(cmd, data, tab);
	return (tab);
}

void	skip_quotes(t_data *data, int arg)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	i = arg;
	if (data && data->cmd && data->cmd[i])
	{
		str = ft_strdup(data->cmd[i]);
		j = -1;
		k = -1;
		while (data->cmd[i][++j])
		{
			if (is_quote(data->cmd[i][j]) == EXIT_FAILURE
			|| (is_quote(data->cmd[i][j]) == EXIT_SUCCESS
			&& check_in_quote(data->cmd[i], data->cmd[i][j], j) > 0))
				str[++k] = data->cmd[i][j];
		}
		k++;
		str[k] = 0;
		secure_free((void **)&data->cmd[i]);
		data->cmd[i] = ft_strdup(str);
		secure_free((void **)&str);
	}
}

t_data	*create_datas(char *cmd, int num, t_list *list)
{
	int		i;
	t_data	*first;
	char	**tab;
	t_data	*data;

	i = 1;
	data = NULL;
	if (num == 1 || cmd[0] == '|')
		return (one_data(cmd, &data, list, 0));
	tab = ft_split(cmd, '|', 0, 1);
	tab[0] = clear_tab(tab[0]);
	data = one_data(tab[i - 1], &data, list, 1);
	first = data;
	num--;
	while (num >= 1)
	{
		tab[i] = clear_tab(tab[i]);
		data->next = one_data(tab[i], &data->next, list, 1);
		i++;
		num--;
		data = data->next;
	}
	free_malloc(tab, cmd, 1);
	data->next = NULL;
	return (first);
}

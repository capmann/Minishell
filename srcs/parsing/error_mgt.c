/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mgt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 21:37:10 by cmarteau          #+#    #+#             */
/*   Updated: 2022/05/05 22:53:53 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	invalid_identifier(t_data *data, t_list *list, int i)
{
	int	j;

	j = 0;
	(void)list;
	if ((data->cmd[i][0] == '=' || !data->cmd[i][0]
		|| !ft_isalpha(data->cmd[i][0])) && data->cmd[i][0] != '_')
	{
		ft_putstr_fd(data->cmd[0], 1);
		ft_putstr_fd(": not a valid identifier\n", 1);
		g_exit_code = 1;
		if (!data->cmd[i + 1])
			return (-1);
		i += 1;
	}
	return (i);
}

int	check_file_exist(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(file);
		return (fd);
	}
	close (fd);
	return (fd);
}

int	check_errors(char *cmd, t_list *list)
{
	t_data	*data;

	data = list->prems;
	if (cmd && cmd[0] == '$' && !cmd[1])
		return (0);
	if (data->cmd && data->cmd[0] == NULL && data->next == NULL)
		return (error_code(0, 1, list));
	if (cmd && check_files(cmd) == -1)
		return (error_code(1, 1, list));
	while (data)
	{
		if (data->cmd && perm_denied(data->cmd[0]) == 1)
			return (error_code(126, 1, list));
		data = data->next;
	}
	return (0);
}

int	syntax_error(char *cmd)
{
	int	i;

	i = -1;
	if (cmd[0] == '|')
		return (1);
	while (cmd[++i])
	{
		if (cmd[i] == '>')
		{
			i++;
			if (cmd[i] && cmd[i] == '<')
				return (1);
			while (cmd[i] && cmd[i] == ' ')
				i++;
			if (cmd[i] && cmd[i] == '>' && cmd[i - 1] != '>')
				return (1);
			if (cmd[i] && cmd[i] == '>' && cmd[i + 1] && cmd[i + 1] == '>')
				return (1);
		}
		if (pipe_errors(cmd, i) == 1)
			return (1);
	}
	return (0);
}

int	pipe_errors(char *cmd, int i)
{
	if (cmd[i] == '|' && char_in_quote(cmd, cmd[i], i) == 0)
	{
		i++;
		while (cmd[i] && cmd[i] == ' ')
			i++;
		if (cmd[i] && (cmd[i] == '|' || cmd[i] == ';')
			&& char_in_quote(cmd, cmd[i], i) == 0)
			return (1);
	}
	return (0);
}

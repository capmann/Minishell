/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mgt_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 21:20:04 by cmarteau          #+#    #+#             */
/*   Updated: 2022/05/07 01:49:53 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	error_code(int exit_code, int error_code, t_list *list)
{
	(void)list;
	g_exit_code = exit_code;
	if (exit_code == 126)
		ft_putstr_fd("Permission denied\n", 1);
	if (exit_code == 2)
		ft_putstr_fd("Syntax error near unexpected token\n", 1);
	return (error_code);
}

int	check_parsing(char *cmd, t_list *list)
{
	t_data	*data;

	if (!cmd)
		return (0);
	ignore_redirect(list);
	if (syntax_error(cmd) == 1)
		return (error_code(2, 1, list));
	data = list->prems;
	while (data)
	{
		open_files(cmd, data);
		get_expansion(data, list);
		if (!data->path)
			gets_path(list, data);
		if (check_errors(cmd, list) == 1)
			return (1);
		if (cmd && data->cmd
			&& check_valid_cmd(cmd, data, list) == EXIT_FAILURE)
		{
			printf("%s: command not found\n", data->cmd[0]);
			return (error_code(127, 1, list));
		}
		data = data->next;
	}
	return (0);
}

int	perm_denied(char *cmd)
{
	int	i;

	i = -1;
	if (!cmd)
		return (0);
	while (cmd[++i])
	{
		if (cmd[i] == '.' && cmd[i + 1] && cmd[i + 1] == '.')
			return (2);
	}
	return (0);
}

int	test_file(char *tmp, int i, int k)
{
	char	*test;

	test = ft_substr(tmp, k, i - k);
	if (check_file_exist(test) == -1)
	{
		secure_free((void **)&test);
		return (-1);
	}
	secure_free((void **)&test);
	return (0);
}

void	check_null_cmd(t_data *data)
{
	int		i;
	char	*tmp;

	i = -1;
	while (data->cmd[++i])
	{
		if (data->cmd[i][0] == 0)
		{
			if (ft_strchr_exp(data->cmd[i], '=') != 0)
			{
				tmp = ft_strdup(ft_strchr_exp(data->cmd[i], '='));
				secure_free((void **)&data->cmd[i]);
				data->cmd[i] = ft_strdup(tmp);
				secure_free((void **)&tmp);
			}
			else
			{
				secure_free((void **)&data->cmd[i]);
				if (data->cmd[i + 1] != NULL)
					data->cmd[i] = ft_strdup(data->cmd[i + 1]);
				data->nb_args--;
			}
		}
	}
}

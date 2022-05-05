/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 18:03:27 by dcyprien          #+#    #+#             */
/*   Updated: 2022/04/28 19:39:11 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_cmds(char *cmd)
{
	int	i;
	int	k;

	k = 1;
	i = -1;
	if (!cmd)
		return (0);
	while (cmd[++i])
	{
		if (cmd[i] && cmd[i] == '|'
			&& char_in_quote(cmd, cmd[i], i) == EXIT_SUCCESS)
			k++;
	}
	return (k);
}

int	is_quote(char c)
{
	if (c == 34 || c == 39)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	check_valid_cmd(char *cmd, t_data *data, t_list *list)
{
	int			i;

	if (is_builtin(data, list) == 1)
		return (EXIT_SUCCESS);
	if (verify_quotes(cmd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	i = 0;
	while (cmd[i] && cmd[i] != ' ')
		i++;
	if (cmd[i] == ' ' && !data->redirect)
	{
		if (!data->path)
		{
			secure_free((void **)&data->path);
			return (EXIT_FAILURE);
		}
	}
	if (!data->path && data->cmd[0] && data->cmd[0][0] != '>'
		&& data->cmd[0][0] != '<' && data->cmd[0][0] != '.')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char	*gets_path(t_list *list, t_data *data)
{	
	char	*tmp;
	char	**tmp_path;
	int		i;
	t_env	*env;

	i = 0;
	tmp_path = NULL;
	tmp = NULL;
	env = list->first;
	if (!data->cmd || cmd_digit(data->cmd[0]) == EXIT_FAILURE)
		return (NULL);
	while (env && ft_strncmp("PATH=", env->env_var, 5))
		env = env->next;
	if (!env)
		return (NULL);
	if (!ft_strncmp("PATH=", env->env_var, 5))
		tmp_path = ft_split(&env->env_var[5], ':', 0, 1);
	return (access_path(tmp_path, tmp, data));
}

t_data	*parsing(char *cmd, t_list *list)
{
	if (!cmd)
		sig_quit(SIGQUIT);
	if (verify_cmd(cmd) == EXIT_FAILURE)
		return (NULL);
	if (null_pipe(cmd) == EXIT_FAILURE)
	{
		error_code(2, 0, list);
		return (NULL);
	}
	list->pipe = count_cmds(cmd) - 1;
	if (count_cmds(cmd) > 0 && verify_cmd(cmd) != 2)
	{
		list->prems = create_datas(cmd, count_cmds(cmd), list);
		if (check_parsing(cmd, list) == 1)
		{
			ft_free_data(list);
			return (NULL);
		}
		return (list->prems);
	}
	return (NULL);
}

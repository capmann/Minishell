/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 01:11:50 by dcyprien          #+#    #+#             */
/*   Updated: 2022/05/05 22:53:30 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_expansion(t_data *data, t_list *list)
{
	int		i;
	int		index;
	char	*a;
	char	*var;

	i = -1;
	if (!data || !data->cmd || ft_strlen(data->cmd[0]) == 0)
		return ;
	while (data->cmd[++i])
	{
		a = ft_strchr_exp(data->cmd[i], '$');
		index = ft_search_index(data->cmd[i], '$');
		if (ft_strlen(data->cmd[i]) == 3 && char_in_quote(data->cmd[i], data->cmd[i][1], 1) > 1)
			return ;
		if (a != 0 && ft_strlen(a) != 1 && (ft_isalnum(data->cmd[i][index + 1])
			|| data->cmd[i][index + 1] == '"' || data->cmd[i][index + 1] == '?')
			&& char_in_quote(data->cmd[i], '$', index) != SIMPLE_QUOTE)
		{
			var = cat_expansion(data->cmd[i], list);
			secure_free((void **)&data->cmd[i]);
			data->cmd[i] = ft_strdup(var);
			i = check_null_cmd(data, i);
			secure_free((void **)&var);
		}
	}
}

char	*cat_expansion(char *cmd, t_list *list)
{
	int		i;
	char	**var;
	char	*res;

	res = NULL;
	var = ft_split(cmd, '$', 0, 2);
	i = -1;
	if (cmd[0] != '$')
		i = 0;
	while (var[++i])
		var[i] = remove_braces(var[i], list);
	var[i] = 0;
	if (i == 1)
		res = ft_strjoin_free(res, var[0]);
	else
	{
		i = -1;
		if (!var[0] && var[1])
			i = 0;
		while (var[++i])
			res = ft_strjoin_free(res, var[i]);
	}
	free_malloc(var, NULL, 1);
	return (res);
}

char	*remove_braces(char *d, t_list *list)
{
	char	**b;
	char	*var;
	char	*c;
	int		i;

	b = NULL;
	c = NULL;
	if (d[0] == '{' && ft_strchr_exp(d, '}') != 0)
	{
		if (ft_strchr_exp(d, '}')[1])
			b = ft_split(d, '}', 0, 1);
		d = ft_substr_free(d, 1, ft_strchr_exp(d, '}') - d - 1);
	}
	i = 0;
	while (d[i] && ((d[i] >= 'A' && d[i] <= 'z') || d[i] == '?'))
		i++;
	if (d[i])
		c = ft_substr(d, i, ft_strlen(d) - 1);
	d = ft_substr_free(d, 0, i);
	var = find_env_var(list, d);
	secure_free((void **)&d);
	return (join_pieces(b, c, var));
}

char	*find_env_var(t_list *list, char *str)
{
	t_env	*env;

	env = list->first;
	if (str && str[0] == '?')
		return (ft_itoa(g_exit_code));
	while (env)
	{
		if (ft_strncmp(env->name, str, ft_strlen(env->name) - 1) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}

char	*join_pieces(char **b, char *c, char *var)
{
	if (b)
	{
		var = ft_strjoin_free(var, b[1]);
		free_malloc(b, NULL, 1);
	}
	if (!b && c)
	{
		var = ft_strjoin_free(var, c);
		secure_free((void **)&c);
	}
	return (var);
}

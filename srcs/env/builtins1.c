/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 01:25:55 by dcyprien          #+#    #+#             */
/*   Updated: 2022/04/10 01:25:56 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	my_unset(t_list *list, t_data *data)
{
	t_env	*env;
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	while (data->cmd[++i])
	{
		i = invalid_identifier(data, list, i);
		if (i == -1)
			return ;
		env = list->first;
		unset_var(list, env, data->cmd[i], tmp);
	}
}

void	unset_var(t_list *list, t_env *env, char *cmd, t_env *tmp)
{
	int	len;
	int	len_n;

	while (env->next)
	{
		len = check_biggest(env->name, cmd);
		len_n = check_biggest(env->next->name, cmd);
		if (env == list->first && \
			((len > 1 && ft_strncmp(env->name, cmd, len) == 0)
				|| (len == 1 && ft_strncmp(env->name, cmd, len) == 0)))
		{
			list->first = env->next;
			secure_free((void **)&env);
			break ;
		}
		else if ((len_n > 1 && ft_strncmp(env->next->name, cmd, len_n - 1) == 0)
			|| (len_n == 1 && ft_strncmp(env->next->name, cmd, len_n) == 0))
		{
			tmp = env->next;
			env->next = env->next->next;
			secure_free((void **)&tmp);
			break ;
		}
		env = env->next;
	}
}

void	my_export(t_list *list, t_data *data)
{
	t_env	*env;
	t_env	*tmp;
	int		len;

	tmp = list->first;
	while (is_sorted(list) == 0)
	{
		env = list->first;
		while (env->next)
		{
			len = check_biggest(env->env_var, env->next->env_var);
			if (ft_strncmp(env->env_var, env->next->env_var, len) > 0)
			{
				list->first = env;
				swap(list);
			}
			env = env->next;
		}
		list->first = tmp;
	}
	if (data->nb_args == 1)
		print_export(list);
}

void	my_export_arg(t_data *data, t_list *list)
{
	t_env	*env;
	int		i;
	char	*tmp;

	i = 0;
	while (data->cmd[++i])
	{
		i = invalid_identifier(data, list, i);
		if (i == -1)
			return ;
		tmp = ft_strchr_exp(data->cmd[i], '=');
		env = malloc(sizeof(*env));
		if (tmp == NULL)
		{
			check_var_exist(list, tmp, data->cmd[i]);
			env->env_var = ft_strdup(data->cmd[i]);
			env->name = ft_strdup(data->cmd[i]);
			env->value = ft_strdup("");
		}
		else
			env = create_env_var(tmp, data->cmd[i], env, list);
		env->next = list->first;
		list->first = env;
	}
	my_export(list, data);
}

t_env	*create_env_var(char *tmp, char *cmd, t_env *env, t_list *list)
{
	check_var_exist(list, tmp, cmd);
	env->name = ft_substr(cmd, 0, tmp - cmd + 1);
	env->value = ft_substr(cmd, tmp - cmd + 1, \
		ft_strlen(cmd));
	env->value = skip_spaces(env->value);
	if (!env->value)
		env->env_var = env->name;
	else
		env->env_var = ft_strjoin(env->name, env->value);
	return (env);
}

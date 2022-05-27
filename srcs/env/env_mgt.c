/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_mgt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 01:35:09 by dcyprien          #+#    #+#             */
/*   Updated: 2022/05/07 00:30:44 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	duplicate_env(char **env, t_list *list)
{
	t_env	*new;
	int		i;
	char	*tmp;

	i = -1;
	tmp = NULL;
	while (env[++i])
	{
		new = malloc(sizeof(*new));
		if (new == NULL)
			return ;
		new->env_var = ft_strdup(env[i]);
		tmp = ft_strchr_exp(env[i], '=');
		new->name = ft_substr(env[i], 0, tmp - env[i] + 1);
		new->value = ft_substr(env[i], tmp - env[i] + 1, ft_strlen(env[i]));
		new->next = list->first;
		list->first = new;
	}
}

t_list	*swap(t_list *list)
{
	t_env	*new;
	char	*tmp;
	char	*tmp1;
	char	*tmp2;

	new = list->first;
	tmp = new->env_var;
	tmp1 = new->name;
	tmp2 = new->value;
	new->env_var = new->next->env_var;
	new->name = new->next->name;
	new->value = new->next->value;
	new->next->env_var = tmp;
	new->next->name = tmp1;
	new->next->value = tmp2;
	return (list);
}

int	is_sorted(t_list *list)
{
	t_env	*new;
	int		len;

	new = list->first;
	while (new->next != NULL)
	{
		len = check_biggest(new->env_var, new->next->env_var);
		if (ft_strncmp(new->env_var, new->next->env_var, len) > 0)
			return (0);
		new = new->next;
	}
	return (1);
}

t_list	*init(char **envp)
{
	t_list	*list;

	list = malloc(sizeof(*list));
	if (list == NULL)
		return (NULL);
	ft_memset(list, 0, sizeof(*list));
	list->first = NULL;
	list->prems = NULL;
	g_exit_code = 0;
	list->pipe = 0;
	duplicate_env(envp, list);
	return (list);
}

void	ft_free_list(t_list *liste)
{
	t_env	*tmp;
	t_env	*tmp2;

	tmp = liste->first;
	while (tmp)
	{
		tmp2 = tmp->next;
		secure_free((void **)&tmp->env_var);
		secure_free((void **)&tmp->name);
		secure_free((void **)&tmp->value);
		secure_free((void **)&tmp);
		tmp = tmp2;
	}
	if (liste)
		secure_free((void **)&liste);
}

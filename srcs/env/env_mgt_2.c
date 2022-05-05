/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_mgt_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 21:37:40 by cmarteau          #+#    #+#             */
/*   Updated: 2022/05/05 22:53:24 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_export(t_list *list)
{
	t_env	*env;

	env = list->first;
	while (env)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env->name, 1);
		if (!env->value || ft_strncmp(env->value, "", 1) == 0)
		{
			if (env->name[ft_strlen(env->name)] == '=')
				ft_putstr_fd("\"\"", 1);
		}
		else
		{
			ft_putchar_fd('\"', 1);
			ft_putstr_fd(env->value, 1);
			ft_putchar_fd('\"', 1);
		}
		ft_putchar_fd('\n', 1);
		env = env->next;
	}
}

void	check_var_exist(t_list *list, char *tmp, char *cmd)
{
	t_env	*check;
	t_env	*check_tmp;
	char	*str;

	check = list->first;
	check_tmp = NULL;
	str = ft_substr(cmd, 0, tmp - cmd + 1);
	unset_var(list, check, str, check_tmp);
	secure_free((void **)&str);
}

void	update_pwd(t_list *list)
{
	t_env	*env;
	char	*tmp;
	char	path[255];

	env = list->first;
	while (env->next && ft_strncmp("PWD", env->name, 3) != 0)
		env = env->next;
	if (ft_strncmp("PWD", env->name, 3) == 0)
	{
		tmp = ft_strdup(env->value);
		secure_free((void **)&env->value);
		if (getcwd(path, sizeof(path)) != NULL)
			env->value = ft_strdup(path);
	}
	env = list->first;
	while (env->next && ft_strncmp("OLDPWD", env->name, 6) != 0)
		env = env->next;
	if (ft_strncmp("OLDPWD", env->name, 6) == 0)
	{
		secure_free((void **)&env->value);
		env->value = ft_strdup(tmp);
	}
	secure_free((void **)&tmp);
}

char	*cd_args(t_list *list, char *str)
{
	t_env	*env;

	env = list->first;
	while (env->next && ft_strncmp(str, env->name, ft_strlen(str)) != 0)
		env = env->next;
	if (ft_strncmp(str, env->name, ft_strlen(str)) == 0)
	{
		if (env->value)
			return (env->value);
		g_exit_code = 0;
		return (NULL);
	}
	ft_putstr_fd("cd: HOME not set\n", 1);
	g_exit_code = 1;
	return (NULL);
}

int	check_biggest(char *s1, char *s2)
{
	if (ft_strlen(s1) > ft_strlen(s2))
		return (ft_strlen(s1));
	return (ft_strlen(s2));
}

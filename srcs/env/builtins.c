/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 01:25:58 by dcyprien          #+#    #+#             */
/*   Updated: 2022/05/05 22:53:21 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	my_echo(t_data *data)
{
	int	i;

	if (ft_strncmp(data->cmd[1], "-n", 2) == 0
		&& skip_n(data->cmd[1]) == 1)
	{
		if (data->nb_args == 2)
			return ;
		i = 1;
		while (ft_strncmp(data->cmd[i], "-n", 2) == 0
			&& skip_n(data->cmd[i]) == 1)
			i++;
		while (i < data->nb_args - 1)
		{
			print_echo(data->cmd[i++]);
			if (i != data->nb_args)
				ft_putchar_fd(' ', 1);
		}
		ft_putstr_fd(data->cmd[i], 1);
	}
	else
		mini_echo(data);
}

void	my_cd(t_data *data, t_list *list)
{
	char	*path;

	if (!data->cmd[1])
	{
		path = cd_args(list, "HOME");
		if (path == NULL)
			return ;
	}
	else if (data->cmd[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 1);
		g_exit_code = 1;
		return ;
	}
	else if (data->cmd[1][0] == '-')
		path = cd_args(list, "OLDPWD");
	else
		path = data->cmd[1];
	if (chdir(path) == -1)
	{
		g_exit_code = 1;
		perror("cd");
	}
	update_pwd(list);
}

void	my_pwd(void)
{
	char	path[255];

	if (getcwd(path, sizeof(path)) != NULL)
	{
		ft_putstr_fd(path, 1);
		ft_putchar_fd('\n', 1);
	}
	else
		perror("getcwd()");
}

void	my_env(t_list *list)
{
	t_env	*env;

	env = list->first;
	while (env)
	{
		if (ft_strchr_exp(env->env_var, '=') != NULL)
		{
			ft_putstr_fd(env->env_var, 1);
			ft_putchar_fd('\n', 1);
		}
		env = env->next;
	}
}

void	my_exit(t_list *list, t_data *data)
{
	if (data)
	{
		if (data->cmd[1] && data->cmd[2])
		{
			ft_putstr_fd("exit: too many arguments\n", 1);
			g_exit_code = 1;
			return ;
		}
		else if (!is_digit_arg(data->cmd[1]))
		{
			ft_putstr_fd("exit: numeric argument required\n", 1);
			g_exit_code = 2;
		}
		else if (data->cmd[1] && data->cmd[1][0] == '-' && !data->cmd[1][1])
			g_exit_code = 255;
		else if (data->cmd[1])
			g_exit_code = ft_atoi(data->cmd[1]);
	}
	ft_free_data(list);
	if (list->prev_pdes)
	{
		close(list->prev_pdes);
		close(STDIN_FILENO);
	}
	exit(g_exit_code);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 17:48:11 by dcyprien          #+#    #+#             */
/*   Updated: 2022/05/05 17:52:03 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	skip_n(char *s)
{
	int	i;

	i = 1;
	while (s[i] && s[i] == 'n')
		i++;
	if (s[i])
		return (0);
	return (1);
}

void	mini_echo(t_data *data)
{
	int	i;

	i = 0;
	while (++i < data->nb_args - 1)
	{
		print_echo(data->cmd[i]);
		if (i != data->nb_args - 1)
			ft_putchar_fd(' ', 1);
	}
	print_echo(data->cmd[i]);
	ft_putchar_fd('\n', 1);
}

int	check_exp(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (0);
	while (cmd[i] && cmd[i] != '$')
		i++;
	if (!cmd[i])
		return (0);
	i += 1;
	while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t'
			|| is_quote(cmd[i]) == EXIT_SUCCESS))
		i++;
	if (cmd[i])
		return (1);
	return (0);
}

int	is_digit_arg(char *s)
{
	int	i;

	i = -1;
	while (s && s[++i])
	{
		if (s[0] == '-')
			s++;
		if (!ft_isdigit(s[i]))
			return (0);
	}
	return (1);
}

int	mini_unset(char *cmd, t_env *env, int len, int mode)
{
	if (mode == 1)
	{
		if ((src_idx(cmd, '=') >= 0 && src_idx(env->next->name, '=') == -1)
			|| (src_idx(cmd, '=') == -1 && src_idx(env->next->name, '=') >= 0))
			return (len - 1);
		return (len);
	}
	if (mode == 2)
	{
		if ((src_idx(cmd, '=') >= 0 && src_idx(env->name, '=') == -1)
			|| (src_idx(cmd, '=') == -1 && src_idx(env->name, '=') >= 0))
			return (len - 1);
		return (len);
	}
	return (len);
}

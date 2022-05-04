/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:14:20 by dcyprien          #+#    #+#             */
/*   Updated: 2022/04/28 17:33:53 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_closed_quotes(char *cmd, int index)
{
	int	i;

	i = index - 1;
	while (cmd[++i])
	{
		if (cmd[i] == 39)
		{
			i += 1;
			while (cmd[i] && cmd[i] != 39)
				i++;
			if (cmd[i] == 39)
				return (SIMPLE_QUOTE);
			return (EXIT_FAILURE);
		}
		if (cmd[i] == 34)
		{
			i += 1;
			while (cmd[i] && cmd[i] != 34)
				i++;
			if (cmd[i] == 34)
				return (DOUBLE_QUOTE);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	get_redirect(char *cmd, t_data *data)
{
	int	i;
	int	redirect[3];

	i = -1;
	redirect[0] = 0;
	redirect[1] = 0;
	redirect[2] = 0;
	while (cmd && cmd[++i])
	{
		if (cmd[i] == '<')
			redirect[0] = 1;
		if (cmd[i] == '>' && char_in_quote(cmd, cmd[i], i) == 0)
		{
			if (cmd[i + 1] && cmd[i + 1] == '>'
				&& char_in_quote(cmd, cmd[i + 1], i + 1) == 0 && i++)
			{
				redirect[1] = 1;
				redirect[2] = 1;
			}
			else
				redirect[1] = 1;
		}
	}
	data = get_redirect_files(cmd, data, redirect[0], redirect[1]);
	return (redirect_tab(redirect));
}

size_t	get_n_arg(char *s, char *c, int start)
{
	size_t	i;
	size_t	j;
	int		quote;

	i = 0;
	j = start;
	if (s[j] == '<')
		j = skip_redirect(s);
	while (s[j])
	{
		if (s[j] && (s[j] == 34 || s[j] == 39))
		{
			quote = s[j++];
			while (s[j] && s[j] != quote)
				j++;
		}
		if (s[j] == '>')
			return (i);
		if ((ft_cinset(s[j], c) && !ft_cinset(s[j - 1], c) && s[j + 1])
			|| (!ft_cinset(s[j], c) && s[j + 1] == '\0')
			|| (!ft_cinset(s[j], c) && s[j + 1] == ' ' && s[j + 2] == '\0'))
			i++;
		j++;
	}
	return (i);
}

int	check_files(char *cmd)
{
	int		i;
	int		k;
	int		count;
	char	*tmp;

	count = count_redir(cmd, '<') + 1;
	tmp = ft_strdup(cmd);
	while (--count)
	{
		i = 0;
		while (tmp[i] != '<' && tmp[i])
			i++;
		if (cmd[i + 1] && cmd[i + 1] == '<')
			break ;
		while (!ft_isalnum(tmp[i]) && !ft_cinset(tmp[i], "./") && tmp[i])
			i++;
		k = i;
		i = file_test(tmp, i, k);
		if (i == -1)
			return (-1);
		tmp = ft_substr_free(tmp, i, ft_strlen(tmp) + 1);
	}
	secure_free((void **)&tmp);
	return (0);
}

int	skip_redirect(char *cmd)
{
	int	i;

	i = 0;
	if (cmd && cmd[i] && cmd[i + 1] == '\0')
		return (i);
	while (cmd && cmd[i])
	{
		if (cmd[i] != '<')
			return (i + 1);
		while ((cmd[i] == '<' || cmd[i] == ' ') && cmd[i])
			i++;
		while (cmd[i] != ' ' && cmd[i])
			i++;
		return (i + 1);
	}
	return (i + 1);
}

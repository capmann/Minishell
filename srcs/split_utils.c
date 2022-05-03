/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 19:44:14 by dcyprien          #+#    #+#             */
/*   Updated: 2022/04/28 21:28:38 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_split	*mini_split(t_split *split, char c, int mode, int q)
{
	while (split->j < split->n_word && split->tmp && *split->tmp)
	{
		while (*split->tmp == c && (*split->tmp != '>' && *split->tmp != '<'))
		{
			split->tmp++;
			if (is_quote(*split->tmp) == EXIT_SUCCESS && mode == 0)
			{
				if (*(split->tmp + 1)
					&& is_quote(*(split->tmp + 1)) == EXIT_FAILURE)
				{
					q = *split->tmp;
					split->res[split->j] = extract_word(split->tmp, q, mode);
					split->tmp = move_tmp(split->tmp, q);
					split->j++;
				}
			}
		}
		if (*split->tmp != '\0')
		{
			split->res[split->j] = extract_word(split->tmp, c, mode);
			split->tmp = ft_strchr(split->tmp, c);
			split->j++;
		}
	}
	return (split);
}

char	*quote_mgt(const char *s, int end)
{
	while (s[end] && s[end] != ' ')
		end++;
	return (ft_substr(s, 0, end + 1));
}

int	is_digit_arg(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
	}
	return (1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 17:28:15 by dcyprien          #+#    #+#             */
/*   Updated: 2022/04/28 21:36:17 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	get_n_word(const char *s, char c, int n, int mode)
{
	size_t	i;

	i = 0;
	while (s && s[n])
	{
		n = handling_quotes((char *)s, n, mode);
		if (s[n] && (s[n] == '<' || s[n] == '>') && ++n)
			while (s[n] && (s[n] == '<' || s[n] == '>' || s[n] == ' '))
				n++;
		if (n && ((s[n] == c && s[n - 1] != c && s[n + 1])
				|| (s[n] && s[n] != c && s[n + 1] == '\0')))
			i++;
		if (s[n])
			n++;
	}
	if (s[n - 1] == c)
		i++;
	if (i == 0)
		i += 1;
	return (i);
}

char	*extract_word(const char *s, char c, int mode)
{
	int		end;

	end = 0;
	if (is_quote(c) == EXIT_SUCCESS && mode != 2)
		end++;
	while (s[end] && s[end] != c)
	{
		end = handling_quotes((char *)s, end, mode);
		if ((s[end] == '>' || s[end] == '<') && ++end)
		{
			if (end > 1 && s[end - 2] && s[end - 2] != ' ')
			{
				end--;
				break ;
			}
			while (s[end] == ' ')
				end++;
		}
		end++;
	}
	if (is_quote(c) == EXIT_SUCCESS && mode != 2)
		return (quote_mgt(s, end));
	return (ft_substr(s, 0, end));
}

char	*move_tmp(char *tmp, int quote)
{
	tmp = ft_strchr(tmp, quote);
	tmp++;
	tmp = ft_strchr(tmp, quote);
	tmp++;
	while (*tmp && *tmp != ' ')
		tmp++;
	return (tmp);
}

t_split	*set_split(const char *s, char c, t_split *split, int mode)
{
	split = malloc(sizeof(t_split));
	split->j = 0;
	split->tmp = ft_strdup(s);
	split->tmptmp = split->tmp;
	split->n_word = get_n_word(s, c, 0, mode);
	split->res = ft_calloc(split->n_word + 1, sizeof(char *));
	return (split);
}

char	**ft_split(const char *s, char c, int start, int mode)
{
	t_split	*split;
	int		quote;
	char	**res;
	int		i;

	split = NULL;
	quote = 0;
	i = -1;
	if (s != NULL && c && *s != 0)
	{
		split = set_split(s, c, split, mode);
		while (--start > 0)
			split->tmp++;
		split = mini_split(split, c, mode, quote);
		split->res[split->j] = NULL;
		if (split->tmptmp)
			secure_free((void **)&split->tmptmp);
		res = ft_calloc(split->n_word + 1, sizeof(char *));
		while (split->res[++i])
			res[i] = split->res[i];
		secure_free((void **)&split->res);
		secure_free((void **)&split);
		return (res);
	}
	return (NULL);
}

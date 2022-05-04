/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 10:53:24 by dcyprien          #+#    #+#             */
/*   Updated: 2022/04/28 21:42:02 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/minishell.h"

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (s != NULL)
	{
		while (*s && *(s + 1) && *s != c)
		{
			if ((*s == '>' || *s == '<') && *s++)
				while (*s == ' ' || *s == '>' || *s == '<')
					s++;
			else
				s++;
			i++;
		}
		if (*s != c && !*(s + 1))
			return ((char *)(s + 1));
		else if (*s == c && check_in_quote(s, *s, i) == 0)
			return ((char *)(s + 1));
		else
			return ((char *)(s + 1));
	}
	return (NULL);
}

int	ft_search_index(const char *s, int c)
{
	int	i;

	i = 0;
	if (s[i])
	{
		while (s[i] && s[i] != c)
			i++;
		if (s[i] != c)
			return (-1);
		else
			return (i);
	}
	return (-1);
}

char	*ft_strchr_exp(const char *s, int c)
{
	unsigned int	i;
	unsigned char	d;

	i = 0;
	d = (unsigned char)c;
	while (s[i] != d && s[i])
		i++;
	if (s[i] == 0 && d != 0)
		return (0);
	return ((char *)&s[i]);
}

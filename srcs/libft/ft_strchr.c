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
	if (s == NULL)
		return (NULL);
	while (*s && *(s + 1) && *s != c)
	{
		if ((*s == '>' || *s == '<') && *s++ && c != '|')
		{
			if (i > 0 && (*s--) && *s--)
				break ;
			while (*s == ' ' || *s == '>' || *s == '<')
				s++;
		}
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

int	src_idx(const char *s, int c)
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

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		size;
	size_t		i;

	i = 0;
	size = ft_strlen((char *)needle);
	if (needle[i] == 0)
		return ((char *)haystack);
	if (len == 0)
		return (0);
	while (haystack[i] && i < len)
	{
		if (haystack[i] == needle[0] && i + size < len + 1)
		{
			if (!ft_strncmp(&haystack[i], needle, size))
				return ((char *)&haystack[i]);
		}
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 10:29:59 by dcyprien          #+#    #+#             */
/*   Updated: 2022/04/07 17:01:20 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*str;
	size_t		i;

	if (s != NULL)
	{
		i = 0;
		if (start >= ft_strlen((char *)s) || !(*s) || len == 0)
			return (NULL);
		str = (char *)malloc(sizeof(char) * (len + 2));
		if (!str)
			return (NULL);
		while (s[start + i] && i < len)
		{
			str[i] = s[start + i];
			i++;
		}
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}

char	*ft_substr_free(char *s, unsigned int start, size_t len)
{
	char		*str;
	size_t		i;

	if (s != NULL)
	{
		i = 0;
		if (start >= ft_strlen((char *)s) || !(*s) || len == 0)
		{
			secure_free((void **)&s);
			return (NULL);
		}
		str = (char *)malloc(sizeof(char) * (len + 2));
		if (!str)
			return (NULL);
		while (s[start + i] && i < len)
		{
			str[i] = s[start + i];
			i++;
		}
		str[i] = '\0';
		secure_free((void **)&s);
		return (str);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 01:35:47 by dcyprien          #+#    #+#             */
/*   Updated: 2022/04/10 01:36:31 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_atoi(const char *str)
{
	unsigned int	res;
	unsigned int	i;
	unsigned int	k;

	res = 0;
	i = 0;
	k = 1;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == 45 && str[i + 1] != 43)
	{
		k = -1;
		i++;
	}
	if (str[i] == 43)
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * k);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (!dst || !src)
		return (0);
	if (dstsize == 0)
	{
		while (src[i])
			i++;
		return (i);
	}
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	while (src[j] != '\0')
		j++;
	return (j);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	len_src;
	unsigned int	len_dst;

	i = 0;
	j = 0;
	len_dst = ft_strlen(dst);
	len_src = ft_strlen((char *)src);
	if (!dst || !src)
		return (0);
	if (dstsize == 0 || len_dst >= dstsize)
		return (len_src + dstsize);
	while (dst[i])
		i++;
	while (src[j] && j < dstsize - len_dst - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (len_src + len_dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*mem;
	unsigned int	len;

	if (!s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	mem = malloc(sizeof(char) * (len + 1));
	if (!mem)
		return (0);
	if (!s1)
		ft_strlcpy(mem, s2, ft_strlen(s2) + 1);
	else
	{
		ft_strlcpy(mem, s1, ft_strlen(s1) + 1);
		ft_strlcat(mem, s2, (ft_strlen(mem) + ft_strlen(s2) + 1));
	}
	return (mem);
}

char	*ft_strjoin_free(char const *s1, char const *s2)
{
	char			*mem;
	unsigned int	len;

	if (!s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	mem = malloc(sizeof(char) * (len + 1));
	if (!mem)
		return (0);
	if (!s1)
		ft_strlcpy(mem, s2, ft_strlen(s2) + 1);
	else
	{
		ft_strlcpy(mem, s1, ft_strlen(s1) + 1);
		ft_strlcat(mem, s2, (ft_strlen(mem) + ft_strlen(s2) + 1));
	}
	if (s1)
		secure_free((void **)&s1);
	return (mem);
}

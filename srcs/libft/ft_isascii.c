/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 09:58:28 by dcyprien          #+#    #+#             */
/*   Updated: 2022/03/29 19:35:03 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isascii(int c)
{
	return (c >= 33 && c <= 127);
}

static int	ft_countletters(int i)
{
	unsigned int	k;

	k = 0;
	if (i < 0)
		k = 1;
	while (i != 0)
	{
		i = i / 10;
		k++;
	}
	return (k);
}

static char	*ft_zero(void)
{
	char	*dest;

	dest = malloc(sizeof(char) * 2);
	if (!dest)
		return (0);
	dest[0] = 48;
	dest[1] = '\0';
	return (dest);
}

char	*ft_itoa(int n)
{
	char			*mem;
	unsigned int	i;
	long			m;

	m = n;
	i = ft_countletters(n);
	if (m == 0 || m == -0)
		return (ft_zero());
	mem = malloc(sizeof(char) * (i + 1));
	if (!mem)
		return (0);
	if (m < 0)
	{
		m = -m;
		mem[0] = '-';
	}
	mem[i] = '\0';
	while (m != 0 && i--)
	{
		mem[i] = m % 10 + 48;
		m = m / 10;
	}
	return (mem);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 01:16:32 by dcyprien          #+#    #+#             */
/*   Updated: 2022/05/07 01:20:40 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_one_list(t_env *list)
{
	t_env	*tmp;

	tmp = list;
	secure_free((void **)&tmp->env_var);
	secure_free((void **)&tmp->name);
	secure_free((void **)&tmp->value);
	secure_free((void **)&tmp);
}

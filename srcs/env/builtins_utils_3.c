/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 23:49:10 by dcyprien          #+#    #+#             */
/*   Updated: 2022/05/07 00:06:15 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	mini_expansion(char *var, t_list *list, t_data *data, int i)
{
	var = cat_expansion(data->cmd[i], list);
	if (char_in_quote(data->cmd[i], '$',
			src_idx(data->cmd[i], '$')) != DOUBLE_QUOTE)
		var = skip_spaces(var);
	secure_free((void **)&data->cmd[i]);
	data->cmd[i] = ft_strdup(var);
	secure_free((void **)&var);
	return (i);
}

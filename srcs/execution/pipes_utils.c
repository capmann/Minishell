/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 18:45:14 by dcyprien          #+#    #+#             */
/*   Updated: 2022/05/05 22:53:36 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	mini_heredoc(t_data *data, char *doc, int *pdes)
{
	doc = heredoc(data);
	if (g_exit_code == 130)
		exit(g_exit_code);
	dup2(pdes[1], STDOUT_FILENO);
	close(pdes[0]);
	ft_putstr_fd(doc, 1);
	close(pdes[1]);
	secure_free((void **)&doc);
	exit(g_exit_code);
}

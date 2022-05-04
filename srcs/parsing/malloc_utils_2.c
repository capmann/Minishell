/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:34:46 by dcyprien          #+#    #+#             */
/*   Updated: 2022/04/28 19:32:50 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	secure_free(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

t_data	*one_data(char *cmd, t_data **data, t_list *list, int mode)
{	
	*data = malloc(sizeof(**data));
	if (!*data)
		return (NULL);
	(*data)->redir_stdin = 0;
	(*data)->redir_stdout = 0;
	(*data)->heredoc = 0;
	(*data)->infile = NULL;
	(*data)->outfile = NULL;
	(*data)->pid = 0;
	(*data)->cmd = get_command(cmd, *data);
	skip_quotes(*data, 0);
	(*data)->path = gets_path(list, *data);
	if (!(*data)->path)
		(*data)->path = verify_path(*data);
	if (mode == 0)
		(*data)->next = NULL;
	return (*data);
}

void	ft_free_data(t_list *liste)
{
	t_data	*tmp;
	t_data	*tmp2;

	tmp = liste->prems;
	if (!liste)
		return ;
	while (tmp)
	{
		tmp2 = tmp->next;
		secure_free((void **)&tmp->path);
		secure_free((void **)&tmp->infile);
		secure_free((void **)&tmp->outfile);
		free_malloc(tmp->cmd, NULL, 1);
		secure_free((void **)&tmp);
		tmp = tmp2;
	}
}

char	*verify_path(t_data *data)
{
	if (data->cmd && data->cmd[0] && cmd_digit(data->cmd[0]) == EXIT_SUCCESS)
	{
		if (access(data->cmd[0], F_OK | X_OK) == 0)
			return (ft_strdup(data->cmd[0]));
	}
	return (NULL);
}

int	redirect_tab(int *redirect)
{
	if ((redirect[0] == 1 || redirect[1] == 1) && redirect[2] == 0)
		return (1);
	else if (redirect[2] == 1)
		return (2);
	return (0);
}

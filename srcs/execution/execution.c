/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 21:36:46 by cmarteau          #+#    #+#             */
/*   Updated: 2022/05/05 22:53:33 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	run_builtin(t_data *data, t_list *list)
{
	if (ft_strncmp(data->cmd[0], "echo", 4) == 0)
		my_echo(data);
	else if (ft_strncmp(data->cmd[0], "cd", 2) == 0)
		my_cd(data, list);
	else if (ft_strncmp(data->cmd[0], "pwd", 3) == 0)
		my_pwd();
	else if (ft_strncmp(data->cmd[0], "env", 3) == 0)
		my_env(list);
	else if (ft_strncmp(data->cmd[0], "export", 6) == 0 && data->nb_args == 1)
		my_export(list, data);
	else if (ft_strncmp(data->cmd[0], "export", 6) == 0 && data->nb_args > 1)
		my_export_arg(data, list);
	else if (ft_strncmp(data->cmd[0], "unset", 5) == 0)
		my_unset(list, data);
	else if (ft_strncmp(data->cmd[0], "exit", 4) == 0)
		my_exit(list, data);
}

int	is_builtin(t_data *data, t_list *list)
{
	if (!data || !data->cmd || !list)
		return (0);
	if (ft_strncmp(data->cmd[0], "echo", 4) == 0
		|| ft_strncmp(data->cmd[0], "cd", 2) == 0
		|| ft_strncmp(data->cmd[0], "pwd", 3) == 0
		|| ft_strncmp(data->cmd[0], "env", 3) == 0
		|| ft_strncmp(data->cmd[0], "export", 6) == 0
		|| ft_strncmp(data->cmd[0], "unset", 5) == 0
		|| ft_strncmp(data->cmd[0], "exit", 4) == 0)
		return (1);
	else
		return (0);
}

void	exec(t_list *list, t_data *data)
{	
	int		exit_status;
	int		pdes[2];
	int		pipes;

	exit_status = -1;
	pipes = list->pipe;
	list->prev_pdes = -1;
	while (data && data->cmd)
	{
		if (data->cmd[0] == 0 && data->next && list->pipe-- && pipes--)
			data = data->next;
		data->pid = run_pipe(data, list, pdes);
		data = data->next;
	}
	if (pipes > 0)
		close(pdes[0]);
	data = list->prems;
	while (data)
	{
		waitpid(data->pid, &exit_status, 0);
		data = data->next;
	}
	if (WIFEXITED(exit_status))
		g_exit_code = WEXITSTATUS(exit_status);
	return ;
}

void	run_shell(t_list *list)
{
	t_data	*data;

	data = list->prems;
	if (data == NULL)
		return ;
	quotes_skip(list);
	if (data->redirect == 0 && list->pipe == 0
		&& is_builtin(data, list) == 1)
	{
		g_exit_code = 0;
		run_builtin(data, list);
	}
	else
		exec(list, data);
}

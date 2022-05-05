/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 21:36:20 by cmarteau          #+#    #+#             */
/*   Updated: 2022/05/05 22:53:44 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

pid_t	run_pipe(t_data *data, t_list *list, int *pdes)
{
	pid_t		pid;

	if (list->pipe > 0)
		pipe(pdes);
	pid = fork();
	disable_signals(pid);
	if (pid == -1)
		return (pid);
	else if (pid == 0)
		child_process(list, data, pdes);
	else
	{
		if (list->pipe > 0)
		{
			close(pdes[1]);
			if (list->prev_pdes != -1)
				close(list->prev_pdes);
			list->prev_pdes = pdes[0];
			list->pipe--;
		}
	}
	return (pid);
}

void	child_process(t_list *list, t_data *data, int *pdes)
{
	if (list->pipe > 0)
	{
		close(pdes[0]);
		dup2(pdes[1], STDOUT_FILENO);
		if (list->prev_pdes != -1)
			dup2(list->prev_pdes, STDIN_FILENO);
		close(pdes[1]);
	}
	if (list->pipe == 0 && list->prev_pdes != -1)
		dup2(list->prev_pdes, STDIN_FILENO);
	if (data->heredoc == 1)
		run_heredoc(data);
	run_redir(data);
	execute_cmd(list, data);
	exit(g_exit_code);
}

void	execute_cmd(t_list *list, t_data *data)
{
	if (is_builtin(data, list) == 0 && list->prems->cmd[0])
	{
		execve(data->path, data->cmd, NULL);
		ft_putstr_fd(data->cmd[0], 1);
		ft_putstr_fd(": Permission denied\n", 1);
		g_exit_code = 2;
	}
	run_builtin(data, list);
	if (list->pipe == 0 && list->prev_pdes != -1)
		close(list->prev_pdes);
	if (list->pipe == 0)
		ft_free_data(list);
}

void	run_heredoc(t_data *data)
{
	pid_t		child;
	int			exit_status;
	int			pdes[2];
	char		*doc;

	pipe(pdes);
	child = fork();
	signal(SIGINT, inthandler2);
	doc = NULL;
	if (child == -1)
		return ;
	else if (child == 0)
		mini_heredoc(data, doc, pdes);
	else
	{
		if (g_exit_code == 130)
			exit(g_exit_code);
		dup2(pdes[0], STDIN_FILENO);
		close(pdes[1]);
		waitpid(child, &exit_status, 0);
	}
}

char	*heredoc(t_data *data)
{
	int		len;
	char	*tmp;
	char	*output;
	char	*test;

	output = NULL;
	set_sigaction(3);
	tmp = readline("> ");
	len = check_biggest(tmp, data->infile);
	while (ft_strncmp(tmp, data->infile, len) != 0)
	{
		test = ft_strjoin(output, tmp);
		secure_free((void **)&output);
		output = ft_strjoin(test, "\n");
		secure_free((void **)&test);
		if (ft_strlen(data->infile) > ft_strlen(tmp))
			len = ft_strlen(data->infile);
		else
			len = ft_strlen(tmp);
		secure_free((void **)&tmp);
		tmp = readline("> ");
	}
	secure_free((void **)&tmp);
	secure_free((void **)&data->infile);
	return (output);
}

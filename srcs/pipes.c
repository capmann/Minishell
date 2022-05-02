/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarteau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 21:36:20 by cmarteau          #+#    #+#             */
/*   Updated: 2022/04/23 21:36:22 by cmarteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

pid_t	run_pipe(t_data *data, t_list *list, int *pdes)
{
	pid_t		pid;

	if (list->pipe > 0)
		pipe(pdes);
	pid = fork();
	if (pid == -1)
		return (pid);
	else if (pid == 0)
		child_process(list, data, pdes);
	parent_process(list, pdes);
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
	if (is_builtin(data, list) == 0)
	{
		execve(data->path, data->cmd, NULL);
		perror("exec error");
	}
	run_builtin(data, list);
	if (list->pipe == 0 && list->prev_pdes != -1)
		close(list->prev_pdes);
	if (list->pipe == 0)
		ft_free_data(list);
	exit(list->exit_code);
}

void	parent_process(t_list *list, int *pdes)
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

void	run_heredoc(t_data *data)
{
	pid_t		child;
	int			pdes[2];
	char		*doc;

	doc = heredoc(data);
	pipe(pdes);
	child = fork();
	if (child == -1)
		return ;
	else if (child == 0)
	{
		dup2(pdes[1], STDOUT_FILENO);
		close(pdes[0]);
		ft_putstr_fd(doc, 1);
		close(pdes[1]);
		exit(0);
	}
	dup2(pdes[0], STDIN_FILENO);
	close(pdes[1]);
	secure_free((void **)&doc);
	wait(NULL);
	return ;
}

char	*heredoc(t_data *data)
{
	int		len;
	char	*tmp;
	char	*output;
	char	*test;

	output = NULL;
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

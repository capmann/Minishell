/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 21:10:49 by cmarteau          #+#    #+#             */
/*   Updated: 2022/05/07 01:06:43 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	run_redir(t_data *args)
{
	int		fd_in;
	int		fd_out;

	if (!args || args->redirect == 0)
		return ;
	if (args->infile && args->heredoc == 0)
	{
		fd_in = open(args->infile, O_RDONLY);
		if (fd_in == -1)
			return ;
		dup2(fd_in, STDIN_FILENO);
		close (fd_in);
	}
	if (args->outfile)
	{
		if (args->redirect == 2)
			fd_out = open(args->outfile, O_WRONLY | O_CREAT | O_APPEND, 00700);
		else
			fd_out = open(args->outfile, O_WRONLY | O_CREAT | O_TRUNC, 00700);
		if (fd_out == -1)
			return ;
		dup2(fd_out, STDOUT_FILENO);
		close (fd_out);
	}
}

char	*last_redir(char *cmd, char c)
{
	int		i;
	int		k;
	char	*tmp;

	i = -1;
	k = 0;
	while (cmd[++i])
		if (cmd[i] == c)
			k++;
	tmp = ft_strchr_exp(cmd, c);
	tmp++;
	while (--k >= 1)
	{
		tmp = ft_strchr_exp(tmp, c);
		tmp++;
	}
	return (tmp);
}

int	count_redir(char *cmd, char c)
{
	int		i;
	int		k;

	i = -1;
	k = 0;
	while (cmd[++i])
		if (cmd[i] == c && char_in_quote(cmd, c, i) == EXIT_SUCCESS
			&& cmd[i + 1] != c)
			k++;
	return (k);
}

void	open_files(char *cmd, t_data *data)
{
	int		i;
	int		k;
	int		count;
	char	*tmp;

	count = count_redir(cmd, '>') + 1;
	tmp = ft_strdup(cmd);
	while (--count)
	{
		i = 0;
		while (tmp[i] != '>' && tmp[i])
			i++;
		data->redir_stdout = 0;
		if (tmp[i] && tmp[i + 1] && tmp[i + 1] == '>')
			data->redir_stdout = 1;
		i += 1;
		while (tmp[i] && !ft_isalnum(tmp[i]) && !ft_cinset(tmp[i], "./"))
			i++;
		k = i;
		if (close_and_open_files(tmp, i, k, data) == -1)
			return ;
		tmp = ft_substr_free(tmp, k + 1, ft_strlen(tmp) + 1);
	}
	secure_free((void **)&tmp);
}

int	close_and_open_files(char *tmp, int i, int k, t_data *data)
{
	char	*file;
	int		fd;

	while (tmp[i] != ' ' && tmp[i])
		i++;
	file = ft_substr(tmp, k, i - k);
	if (data->redir_stdout == 0)
		fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 00700);
	else
		fd = open(file, O_RDWR | O_CREAT | O_APPEND, 00700);
	close(fd);
	if (fd == -1)
		secure_free((void *)&tmp);
	secure_free((void **)&file);
	return (fd);
}

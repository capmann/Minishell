/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 23:55:40 by dcyprien          #+#    #+#             */
/*   Updated: 2022/05/05 19:27:05 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	verify_quotes(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == 92 && char_in_quote(cmd, cmd[i], i) == EXIT_SUCCESS)
			return (EXIT_FAILURE);
		if (cmd[i] == ';' && char_in_quote(cmd, cmd[i], i) == EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	get_outfile(char *cmd, t_data *data)
{
	int		i;
	int		k;
	char	*tmp;

	i = 0;
	tmp = last_redir(cmd, '>');
	while (tmp[i] && !ft_isalnum(tmp[i]) && !ft_cinset(tmp[i], "./"))
		i++;
	k = i;
	while (tmp[i] != ' ' && tmp[i])
		i++;
	data->outfile = ft_substr(tmp, k, i - k);
}

void	get_infile(char *cmd, t_data *data)
{
	int		i;
	int		k;
	char	*tmp;

	i = 0;
	while (cmd[i] != '<' && cmd[i])
		i++;
	if (cmd[i + 1] && cmd[i + 1] == '<')
		data->heredoc = 1;
	i = 0;
	tmp = last_redir(cmd, '<');
	while (!ft_isalnum(tmp[i]) && !ft_cinset(tmp[i], "./") && tmp[i])
		i++;
	k = i;
	while (tmp[i] != ' ' && tmp[i])
		i++;
	data->infile = ft_substr(tmp, k, i - k);
	data->redir_stdin = count_redir(cmd, '<');
}

t_data	*get_redirect_files(char *cmd, t_data *data, int infile, int outfile)
{
	if (infile == 1)
		get_infile(cmd, data);
	if (outfile)
		get_outfile(cmd, data);
	return (data);
}

char	*clear_tab(char *str)
{
	int		i;
	char	*new;
	char	*tmp;
	int		k;

	i = 0;
	new = NULL;
	tmp = NULL;
	if (!str)
		return (NULL);
	if (str)
	{
		while ((str[i] == ' ' || str[i] == '\t') && str[i])
			i++;
		tmp = ft_substr(str, i, ft_strlen(str) - i);
		secure_free((void **)&str);
	}
	k = ft_strlen(tmp) - 1;
	i = 0;
	while (tmp && tmp[k] && (tmp[k] == ' ' || tmp[k] == '\t') && k--)
		i++;
	new = ft_substr(tmp, 0, ft_strlen(tmp) - i);
	secure_free((void **)&tmp);
	return (new);
}

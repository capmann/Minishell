/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:48:56 by dcyprien          #+#    #+#             */
/*   Updated: 2022/05/06 00:21:03 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_code;

int	main(int ac, char **av, char **envp)
{
	char				*prompt;
	int					std_copy;
	t_list				*list;

	(void)av;
	std_copy = dup(0);
	if (ac != 1)
	{
		ft_putstr_fd("Error: too many arguments\n", 1);
		exit(0);
	}
	list = init(envp);
	while (42)
	{
		set_sigaction(0);
		prompt = readline("Mimi_shell>> ");
		list->prems = parsing(prompt, list);
		run_shell(list);
		ft_free_data(list);
		secure_free((void **)&prompt);
		dup2(std_copy, STDIN_FILENO);
		close(std_copy);
	}
	return (g_exit_code);
}

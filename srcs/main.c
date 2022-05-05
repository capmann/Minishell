/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:48:56 by dcyprien          #+#    #+#             */
/*   Updated: 2022/05/05 22:53:14 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_code;

int	main(int ac, char **av, char **envp)
{
	char				*prompt;
	int					stdin_copy;
	t_list				*list;

	(void)av;
	stdin_copy = dup(0);
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
		if (ft_strlen(prompt) > 0)
			add_history(prompt);
		list->prems = parsing(prompt, list);
		run_shell(list);
		ft_free_data(list);
		secure_free((void **)&prompt);
		dup2(stdin_copy, STDIN_FILENO);
	}
	ft_free_list(list);
	rl_clear_history();
	return (g_exit_code);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:48:56 by dcyprien          #+#    #+#             */
/*   Updated: 2022/04/28 21:29:43 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char				*prompt;
	t_list				*list;
	struct sigaction	act;

	if (ac != 1)
	{
		ft_putstr_fd("Error: too many arguments\n", 1);
		return (0);
	}
	(void)av;
	ft_memset(&act, 0, sizeof(act));
	set_sigaction(act);
	list = init(envp);
	while (42)
	{
		prompt = readline("Mimi_shell>> ");
		if (ft_strlen(prompt) > 0)
			add_history(prompt);
		list->prems = parsing(prompt, list);
		run_shell(list);
		ft_free_data(list);
		secure_free((void **)&prompt);
	}
	ft_free_list(list);
	rl_clear_history();
	return (list->exit_code);
}

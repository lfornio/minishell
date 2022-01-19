/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:38:49 by lfornio           #+#    #+#             */
/*   Updated: 2022/01/18 16:34:41 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	argv_is_not(char **argv)
{
	char	*s;

	s = argv[0];
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*line;

	global_status = 0;
	line = NULL;
	argv_is_not(argv);
	if (argc != 1)
	{
		printf("Error arguments\n");
		return (1);
	}
	while (1)
	{
		line = readline("\001\033[32m\002minishell> \001\033[0m\002");
		add_history(line);
		if (parsing(&data, line, envp) < 0)
			continue ;
		print_data(&data); //убрать потом, печатает основную структуру
		if (execution(&data, line) < 0)
			continue ;
	}
	return (0);
}

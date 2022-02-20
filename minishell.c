/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:38:49 by lfornio           #+#    #+#             */
/*   Updated: 2022/02/20 17:08:16 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	argv_is_not(char **argv)
{
	char	*s;

	s = argv[0];
}

void	init_data(t_data *data)
{
	data->count_commands = 0;
	data->count_pipe = 0;
	data->commands = NULL;
	data->prepars = NULL;
}

int	parsing(t_data *data, char *line, t_envp *env)
{
	init_data(data);
	if (preparsing(data, line) < 0)
	{
		free_all(data);
		free(line);
		return (-1);
	}
	if (complete_data(data, env) < 0)
	{
		free_all(data);
		free(line);
		return (-1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_envp	env_struct;
	char	*line;

	global_status = 0;
	line = NULL;
	argv_is_not(argv);
	init_env(&env_struct, envp);
	if (argc != 1)
	{
		printf("Error arguments\n");
		return (1);
	}
	while (1)
	{
		line = readline("\001\033[32m\002minishell> \001\033[0m\002");
		add_history(line);
		if (parsing(&data, line, &env_struct) < 0)
			continue ;
		print_data(&data); //убрать потом, печатает основную структуру
		if (execution(&data, line) < 0)
			continue ;
	}
	free_env_struct(&env_struct);
	return (0);
}

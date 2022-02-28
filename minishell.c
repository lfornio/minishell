/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshad <mshad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:38:49 by lfornio           #+#    #+#             */
/*   Updated: 2022/02/26 19:24:39 by mshad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_arguments(int argc, char **argv)
{
	if (argc != 1)
	{
		printf("Error arguments\n");
		exit(1);
	}
	(void)argv;
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

static int	ft_minishell(t_data *data, char *line, t_envp *env_struct)
{
	add_history(line);
	if (parsing(data, line, env_struct) < 0)
		return (-1);
	if (execution(data, env_struct) < 0)
	{
		free_all(data);
		free(line);
		return (-1);
	}
	close_fd(data);
	free_all(data);
	free(line);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_envp	env_struct;
	char	*line;

	g_status = 0;
	line = NULL;
	ft_arguments(argc, argv);
	init_env(&env_struct, envp);
	rl_outstream = stderr;
	signals();
	while (1)
	{
		line = readline("\001\033[32m\002minishell> \001\033[0m\002");
		if (!(line))
			input_eof();
		if (ft_minishell(&data, line, &env_struct) < 0)
			continue ;
	}
	free_env_struct(&env_struct);
	return (0);
}

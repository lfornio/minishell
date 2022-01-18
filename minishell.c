/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:38:49 by lfornio           #+#    #+#             */
/*   Updated: 2022/01/18 11:41:35 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_status = 0;

int main(int argc, char **argv, char **envp)
{
	if (argc != 1)
	{
		printf("Error arguments\n");
		exit(1);
	}
	char *s;
	s = argv[0];
	t_data data;
	// t_cmd command_for_fork;echo
	// init_cmd(&command_for_fork);

	global_status = 0;

	printf("global_status_init = %d\n", global_status);
	char *line;
	while (1)
	{
		init_data(&data);
		line = readline("\001\033[32m\002minishell> \001\033[0m\002");
		add_history(line);
		// print_data(&data);
		if (preparsing(&data, line) < 0)
		{
			printf("global_status_1 = %d\n", global_status);
			free_all(&data);
			free(line);
			continue;
		}
		// print_list_prepars(data.prepars);
		printf("============================\n");
		// print_data(&data);
		if(complete_data(&data, envp) < 0)
		{
			printf("global_status_2 = %d\n", global_status);
			free_all(&data);
			free(line);
			continue;
		}
		// print_data(&data);
		int a;
		a = processing(&data);





		global_status = 0;
		printf("global_status_norm = %d\n", global_status);
		free_all(&data);
		// printf("1-----------1\n");
		// print_data(&data);
		free(line);
	}
	return (0);
}

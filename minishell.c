/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:38:49 by lfornio           #+#    #+#             */
/*   Updated: 2022/01/10 15:26:54 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	init_data(&data);
	char *line;
	while (1)
	{
		line = readline("\001\033[32m\002minishell> \001\033[0m\002");
		add_history(line);
		if (preparsing(&data, line) < 0)
		{
			if (!data.prepars)
			{
				free_list_prepars(&data.prepars);
				free(line);
			}
			continue;
		}
		print_list_prepars(data.prepars);
		printf("============================\n");
		complete_data(&data, envp);
		// if (!data.commands)
		// {
		// 	free_list_prepars(&data.prepars);
		// 	free_list(&data.envp_list);
		// 	for (int i = 0; data.arr_envp[i]; i++)
		// 		free(data.arr_envp[i]);
		// 	free(data.arr_envp);
		// 	free(line);
		// 	continue;
		// }
		// free_all(&data);
		free(line);
	}
	return (0);
}

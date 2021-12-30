/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:38:49 by lfornio           #+#    #+#             */
/*   Updated: 2021/12/30 11:09:14 by lfornio          ###   ########.fr       */
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
	t_data data;

	char *s;
	s = argv[0];
	//readline - работает
	char *line;
	// for(int i = 0; envp[i]; i++)
	// 	printf("%s\n", envp[i]);
	// while(1)
	// {
	// line = "$USER  $\"PWD\" $USER";
	line = readline("\001\033[32m\002minishell> \001\033[0m\002");
	add_history(line);
	// printf("s = %s\n", line);

	// }
	t_prepars *prepars_list;
	prepars_list = preparsing_str(line);						   //создали список для препарса
	error_prepars_str(prepars_list, line);						   //exit если " и ' не закрыты
	removing_spaces_and_tabs(prepars_list);						   //убрали лишние пробелы и табуляции
	search_for_commands(prepars_list);							   // ищем |
	gluing_strings_without_pipe(prepars_list);					   // скдеили строки без |
	removing_spaces_at_the_beginning_and_end_in_str(prepars_list); //удалили пробелы в начале и конце каждой строки
	error_last_pipe(prepars_list);								   // удаляет последний пустой узел и ошибка если последний узкл - пайп

	data.count_pipe = count_pipes(prepars_list); //посчитали сколько пайпов
	printf("count_pipe = %d\n", data.count_pipe);
	delete_node_with_pipe(prepars_list); //удалили пайпы
	print_list_prepars(prepars_list);
	printf("============================\n");

	data.count_commands = data.count_pipe + 1;//количество команд
	data.exit_code = 1;

	data.envp_list = get_envp_list(envp); //envp сохранили в список
	 // print_list(&envp_list);
	 // printf("============================\n");
	data.arr_envp = envp_list_remake_arr(data.envp_list); //список envp сохранили в массив строк


	data.commands = push_node_cmd_firs(&data, prepars_list); // еще не завершила. создала только один узел


	free_list_prepars(&prepars_list);

	free_list(&data.envp_list);
	for(int i = 0; data.arr_envp[i]; i++)
		free(data.arr_envp[i]);
	free(data.arr_envp);
	for(int i = 0; data.commands->tab_cmd[i]; i++)
		free(data.commands->tab_cmd[i]);
	free(data.commands->tab_cmd);
	free(data.commands->argument);
	free(data.commands->full_str);
	free(data.commands->command);
	free(data.commands);
	free(line);


	return (0);
}

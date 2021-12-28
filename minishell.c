/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:38:49 by lfornio           #+#    #+#             */
/*   Updated: 2021/12/28 17:21:15 by lfornio          ###   ########.fr       */
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

	data.envp_list = get_envp_list(envp); //envp сохранили в список
	 // print_list(&envp_list);
	 // printf("============================\n");
	data.arr_envp = envp_list_remake_arr(data.envp_list); //список envp сохранили в массив строк


	// t_cmd *commands = NULL;
	data.commands = push_node_cmd_firs(&data, prepars_list); // еще не завершила. создала только один узел



	//сделать функцию которая список сохраняет в массив строк
	//сделать ф-цию которая ищет в среде окружения ключ
	//заменяет или удаляет из строки

	// change_dollar(commands);

	// char **prepars_arr_str;     //записали список в массив строк
	// prepars_arr_str = (char **)malloc(sizeof(char*) * (size + 1));
	// if(!prepars_arr_str)
	// 	return(1);
	// int i = 0;

	// while(prepars_list)
	// {
	// 	prepars_arr_str[i] = prepars_list->str;
	// 	i++;
	// 	prepars_list = prepars_list->next;
	// }
	// for(int i = 0; prepars_arr_str[i]; i++)
	// 	printf("s = %s\n", prepars_arr_str[i]);

	free_list_prepars(&prepars_list);
	free_list(&data.envp_list);
	for(int i = 0; data.arr_envp[i]; i++)
		free(data.arr_envp[i]);
	free(data.arr_envp);
	free(data.commands->full_str_without_dollar);
	free(data.commands->full_str);
	free(data.commands->cmd);
	free(data.commands);
	free(line);

	/*
	int i;
	i = 0;
	int count_semicolon;
	count_semicolon = 0;
	int count_pipe;
	count_pipe = 0;

	while (str[i])        //посчитали сколько в строке ; и |
	{
		if (str[i] == ';')
		{
			count_semicolon++;
		}
		if (str[i] == '|')
			count_pipe++;

		i++;
	}
	printf("str = %s\n", str);
	printf("count_semicolon = %d; count_pipe = %d\n", count_semicolon, count_pipe);
	int *arr_index_semicolon;      //создали массив интов индексов  для ;
	arr_index_semicolon = (int *)malloc(sizeof(int) * count_semicolon);
	if (!arr_index_semicolon)
	{
		printf("Error malloc\n");
		exit(1);
	}
	i = 0;
	int j;
	j = 0;
	while(str[i])                  //внесли в массив индексы ;
	{
		if(str[i] == ';')
		{
			arr_index_semicolon[j] = i;
			j++;
		}
		i++;
	}
	for(int i = 0; i < count_semicolon; i++)
		printf("%d ", arr_index_semicolon[i]);
	printf("\n");

	i = 0;
	int count_single_quote;
	count_single_quote = 0;
	int count_double_quote;
	count_double_quote = 0;
	while(str[i])
	{
		if(str[i] == ';' || str[i] == '|')      //считаем сколько ' и " до первого ; или |
			break ;
		if(str[i] == '\'')
			count_single_quote++;
		if(str[i] == '\"')
			count_double_quote++;
		i++;
	}
	printf("count_single_quote = %d; count_double_quote = %d\n", count_single_quote, count_double_quote);
	if(count_single_quote % 2 || count_double_quote % 2)
*/

	return (0);
}

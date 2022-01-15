/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:42:42 by lfornio           #+#    #+#             */
/*   Updated: 2022/01/15 18:17:59 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void pars_envp_str(t_list *list, char *str) //функция парсит строку из envp на массив строк: tab[0] - ключ(до =), tab[1] - значение(после =) и записывает в узел
{
	char **tab;
	tab = ft_split(str, '=');
	list->key = tab[0];
	list->value = tab[1];
	free(tab);
}

void push_node(t_list **list, char *str) //функция создает 1ый узел
{
	t_list *new;
	new = malloc(sizeof(t_list));
	if (!new)
	{
		printf("Error malloc\n");
		return;
		;
	}
	pars_envp_str(new, str);
	new->next = *list;
	*list = new;
}

void push_last_node(t_list **list, char *str) //функция добавляет узел в конец списка
{
	t_list *tmp;
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;

	t_list *new;
	new = malloc(sizeof(t_list));
	if (!new)
	{
		printf("Error malloc\n");
		return;
	}
	pars_envp_str(new, str);
	new->next = NULL;
	tmp->next = new;
}

void print_list(t_list **list) //печатает список
{
	t_list *p;
	p = *list;
	while (p != NULL)
	{
		printf("%s=%s\n", p->key, p->value);
		p = p->next;
	}
}

int found_char_c(char *str, char c) //ищем с
{
	int i;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void init_data(t_data *data)
{
	data->count_commands = 0;
	data->count_pipe = 0;
	data->commands = NULL;
	data->envp_list = NULL;
	data->arr_envp = NULL;
	data->exit_code = 0;
	data->prepars = NULL;
}

int complete_data(t_data *data, char **envp)
{
	int flag;
	flag = 0;
	// printf("count_com = %d\n", data->count_commands);
	// printf("count_pipe = %d\n", data->count_pipe);
	// printf("commands_list = %p\n", data->commands);
	// printf("envp_list = %p\n", data->envp_list);
	// printf("envp_arr = %p\n", data->arr_envp);
	// printf("exit_code = %d\n", data->exit_code);
	// printf("prepars = %p\n", data->prepars);

	data->count_pipe = count_pipes(data->prepars);			//посчитали сколько пайпов
	delete_node_with_pipe(data->prepars);					//удалили пайпы
	data->count_commands = data->count_pipe + 1;			//количество команд
	data->envp_list = get_envp_list(envp);					//envp сохранили в список
	data->arr_envp = envp_list_remake_arr(data->envp_list); //список envp сохранили в массив строк
	t_prepars *ptr;
	ptr = data->prepars;
	while (ptr)
	{
		if (flag == 0)
		{
			if (push_node_cmd_firs(&data->commands, ptr, data) < 0)
				return(-1);
		}
		else
			push_last_node_cmd_firs(&data->commands, ptr, data, flag);
		flag++;
		ptr = ptr->next;
	}
	return(0);
}


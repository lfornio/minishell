/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:42:42 by lfornio           #+#    #+#             */
/*   Updated: 2022/01/11 15:27:41 by lfornio          ###   ########.fr       */
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

void free_list(t_list **list) // удаляет список
{
	t_list *p;

	p = NULL;
	if (!*list)
		return;
	while (*list)
	{
		p = *list;
		*list = (*list)->next;
		free(p->key);
		free(p->value);
		free(p);
	}
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

void complete_data(t_data *data, char **envp)
{
	int flag;
	flag = 0;
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
				return;

		}
		else
		{
			push_last_node_cmd_firs(&data->commands, ptr, data, flag);

		}
		flag++;
		ptr = ptr->next;
	}
}

void free_all(t_data *data)
{
	free_list_prepars(&data->prepars);
	free_list(&data->envp_list);
	for (int i = 0; data->arr_envp[i]; i++)
		free(data->arr_envp[i]);
	free(data->arr_envp);
	for (int i = 0; data->commands->tab_cmd[i]; i++)
		free(data->commands->tab_cmd[i]);
	free(data->commands->tab_cmd);
	free(data->commands->argument);
	free(data->commands->full_str);
	free(data->commands->command);
	free(data->commands);
}

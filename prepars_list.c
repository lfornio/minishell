/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepars_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 11:36:18 by lfornio           #+#    #+#             */
/*   Updated: 2022/01/15 15:32:10 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int preparsing(t_data *data, char *line)
{
	t_prepars *prepars_list;

	prepars_list = preparsing_str(line);
	data->prepars = prepars_list;
	if (!prepars_list)
		return (-1);				   //создали список для препарса
	if (error_quote(prepars_list) < 0) // незакрытые кавычки
		return (-1);
	removing_spaces_and_tabs_in_list(prepars_list);
	if (search_for_pipes(prepars_list) < 0)
		return (-1);
	gluing_strings_without_pipe(prepars_list); // скдеили строки без |
	if (removing_spaces_at_the_beginning_and_end_in_str(prepars_list) < 0) //удалили пробелы в начале и конце каждой строки
		return (-1);

	if (error_last_pipe(prepars_list) < 0)
		return (-1); // удаляет последний пустой узел и ошибка если последний узкл - пайп
	return (0);
}

void free_list_prepars(t_prepars **list) //чистит список препарса
{
	t_prepars *p;

	p = NULL;
	if (!*list)
		return;
	while (*list)
	{
		p = *list;
		*list = (*list)->next;
		if (p->str)
			free(p->str);
		free(p);
	}
}

void print_list_prepars(t_prepars *list) //печатает список препарса
{
	t_prepars *p;
	p = list;
	while (p != NULL)
	{
		printf("%s\n", p->str);
		p = p->next;
	}
}

void push_node_prepars(t_prepars **list, char *str) //функция создает 1ый узел для препарсинга
{
	t_prepars *new;
	char *s;
	s = ft_strdup(str);
	new = malloc(sizeof(t_prepars));
	if (!new)
	{
		printf("Error malloc\n");
		return;
	}
	new->str = s;
	new->next = *list;
	*list = new;
}

void push_last_node_prepars(t_prepars **list, char *str) //функция добавляет узел в конец списка для препарсинга
{
	t_prepars *tmp;
	char *s;
	s = ft_strdup(str);
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;

	t_prepars *new;
	new = malloc(sizeof(t_prepars));
	if (!new)
	{
		printf("Error malloc\n");
		return;
	}
	new->str = s;
	new->next = NULL;
	tmp->next = new;
}

void delete_last_node_prepars(t_prepars *p, t_prepars *head) // удаляет последний узел в списке
{
	t_prepars *tmp;

	tmp = head;
	while (tmp->next != p)
		tmp = tmp->next;
	tmp->next = NULL;
	free(p->str);
	free(p);
}

t_prepars *get_ptr_from_list(t_prepars *list, int index) // функция берет указатель по индексу в списке
{
	t_prepars *p;
	int i;

	i = 1;
	p = list;
	while (i < index)
	{
		p = p->next;
		i++;
	}
	return (p);
}

t_prepars *a_new_node_in_the_middle(t_prepars *middle, char *str) //добавляем новый узел в середину
{
	t_prepars *new;
	t_prepars *tmp;
	new = malloc(sizeof(t_prepars));
	if (!new)
		return (NULL);
	tmp = middle->next;
	middle->next = new;
	new->str = ft_strdup(str);
	new->next = tmp;
	return (new);
}

t_prepars *delete_node_prepars(t_prepars *p, t_prepars *head) //удаляет узел в середине списка
{
	t_prepars *tmp;

	tmp = head;
	while (tmp->next != p)
		tmp = tmp->next;
	tmp->next = p->next;
	free(p->str);
	free(p);
	return (tmp);
}

char *get_str_from_list(t_prepars *list, int index) // функция берет строку по индексу в списке
{
	t_prepars *p;
	int i;
	char *str;

	i = 1;
	p = list;
	while (i < index)
	{
		p = p->next;
		i++;
	}
	str = p->str;
	p = NULL;
	free(p);
	return (str);
}

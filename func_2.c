/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 11:14:03 by lfornio           #+#    #+#             */
/*   Updated: 2021/12/29 11:09:51 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void free_list_prepars(t_prepars **list)     //чистит список препарса
{
	t_prepars *p;

	p = NULL;
	if (!*list)
		return;
	while (*list)
	{
		p = *list;
		*list = (*list)->next;
		free(p->str);
		free(p);
	}
}

void print_list_prepars(t_prepars *list)    //печатает список препарса
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
		exit(1);
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
		exit(1);
	}
	new->str = s;
	new->next = NULL;
	tmp->next = new;
}

char *ft_quote(char *str, int *i, char c) // функция обрабатывает  ' и " в строке
{
	int a;
	a = *i;
	(*i)++;
	int count;
	count = 1;
	char *tmp;
	while (str[*i])
	{
		if (str[*i] == c)
			break;
		count++;
		(*i)++;
	}
	if (str[*i] == c)
		count++;
	tmp = ft_substr(str, a, count);
	return (tmp);
}

char *ft_non(char *str, int *i)    //функция обрабатывает символы отличные от  ' "
{
	int a;
	int count;
	char *tmp;

	a = *i;
	count = 0;
	while (str[*i] && str[*i] != '\'' && str[*i] != '\"')
	{
		count++;
		(*i)++;
	}
	(*i)--;
	tmp = ft_substr(str, a, count);
	return (tmp);
}

t_prepars *preparsing_str(char *str)   //функция делить строку на список разделенный на "" ''  символы
{
	int i = 0;
	char *tmp;
	int j = 0;
	t_prepars *prepars_list = NULL;

	while (str[i])
	{
		if (str[i] == '\'')
			tmp = ft_quote(str, &i, '\'');
		else if (str[i] == '\"')
			tmp = ft_quote(str, &i, '\"');
		else
			tmp = ft_non(str, &i);
		if (j == 0)
			push_node_prepars(&prepars_list, tmp);
		else
			push_last_node_prepars(&prepars_list, tmp);
		free(tmp);
		j++;
		i++;
	}
	return (prepars_list);
}

int size_list_prepars(t_prepars *list)  //функция считает размер списка препарса
{
	int count;
	count = 0;

	if(!list)
		return(-1);
	while(list)
	{
		count++;
		list = list->next;
	}
	return(count);

}

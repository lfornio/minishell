/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:42:42 by lfornio           #+#    #+#             */
/*   Updated: 2021/12/15 16:08:03 by lfornio          ###   ########.fr       */
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
		exit(1);
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
		exit(1);
	}
	pars_envp_str(new, str);
	new->next = NULL;
	tmp->next = new;
}

void free_list(t_list **list)
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

void print_list(t_list **list)
{
	t_list *p;
	p = *list;
	while (p != NULL)
	{
		printf("%s=%s\n", p->key, p->value);
		p = p->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_10.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 12:08:56 by lfornio           #+#    #+#             */
/*   Updated: 2022/01/18 20:00:46 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void push_node(t_list **list, char *str) //функция создает 1ый узел
{
	t_list *new;
	new = malloc(sizeof(t_list));
	if (!new)
	{
		printf("Error malloc\n");
		return;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepars_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 11:36:18 by lfornio           #+#    #+#             */
/*   Updated: 2022/01/18 19:21:28 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
функция создает 1ый узел для препарсинга
*/
void	push_node_prepars(t_prepars **list, char *str)
{
	t_prepars	*new;
	char		*s;

	s = ft_strdup(str);
	new = (t_prepars *)malloc(sizeof(t_prepars));
	if (!new)
		return ;
	new->str = s;
	new->next = *list;
	*list = new;
}

/*
функция добавляет узел в конец списка для препарсинга
*/
void	push_last_node_prepars(t_prepars **list, char *str)
{
	t_prepars	*tmp;
	t_prepars	*new;
	char		*s;

	s = ft_strdup(str);
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	new = (t_prepars *)malloc(sizeof(t_prepars));
	if (!new)
		return ;
	new->str = s;
	new->next = NULL;
	tmp->next = new;
}

/*
удаляет последний узел в списке
*/
void	delete_last_node_prepars(t_prepars *p, t_prepars *head)
{
	t_prepars	*tmp;

	tmp = head;
	while (tmp->next != p)
		tmp = tmp->next;
	tmp->next = NULL;
	free(p->str);
	free(p);
}

/*
добавляем новый узел в середину
*/
t_prepars	*a_new_node_in_the_middle(t_prepars *middle, char *str)
{
	t_prepars	*new;
	t_prepars	*tmp;

	new = (t_prepars *)malloc(sizeof(t_prepars));
	if (!new)
		return (NULL);
	tmp = middle->next;
	middle->next = new;
	new->str = ft_strdup(str);
	new->next = tmp;
	return (new);
}

/*
удаляет узел в середине списка
*/
t_prepars	*delete_node_prepars(t_prepars *p, t_prepars *head)
{
	t_prepars	*tmp;

	tmp = head;
	while (tmp->next != p)
		tmp = tmp->next;
	tmp->next = p->next;
	free(p->str);
	free(p);
	return (tmp);
}

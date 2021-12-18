/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 10:17:05 by lfornio           #+#    #+#             */
/*   Updated: 2021/12/18 11:36:25 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_prepars *delete_node_prepars(t_prepars *p, t_prepars *head)  //удаляет узел в середине списка
{
	t_prepars *tmp;
	tmp = head;
	while(tmp->next != p)
		tmp = tmp->next;
	tmp->next = p->next;
	free(p->str);
	free(p);
	return(tmp);
}

void gluing_strings_without_quotes(t_prepars **list)   //функция склеивает строки без ' и " в списке
{
	t_prepars *p;
	t_prepars *head;
	p = *list;
	head = *list;
	char *s1;
	char *s2;
	char *tmp;
	int index = 1;
	while (p && p->next)
	{
		s1 = get_str_from_list(head, index);
		s2 = get_str_from_list(head, index + 1);
		if (s1[0] != '\'' && s1[0] != '\"' && s2[0] != '\'' && s2[0] != '\"')
		{
			tmp = ft_strjoin(s1, s2);
			free(p->str);
			p->str = ft_strdup(tmp);
			free(tmp);
			p= p->next;
			p = delete_node_prepars(p, head);
		}
		else
		{
			index++;
			p= p->next;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 10:17:05 by lfornio           #+#    #+#             */
/*   Updated: 2022/01/07 13:43:03 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_prepars *found_str_without_pipe_for_gluing(t_prepars *p, t_prepars *head, int *index)
{
	char *s1;
	char *s2;
	char *tmp;

	s1 = get_str_from_list(head, *index);
	s2 = get_str_from_list(head, *index + 1);
	if (s1[0] != '|' && s2[0] != '|')
	{
		tmp = ft_strjoin(s1, s2);
		free(p->str);
		p->str = ft_strdup(tmp);
		free(tmp);
		p = p->next;
		p = delete_node_prepars(p, head);
	}
	else
	{
		(*index)++;
		p = p->next;
	}
	return (p);
}

void gluing_strings_without_pipe(t_prepars *list) //функция склеивает строки без ' и " в списке
{
	t_prepars *p;
	t_prepars *head;
	p = list;

	head = list;
	int index = 1;
	while (p && p->next)
		p = found_str_without_pipe_for_gluing(p, head, &index);
}

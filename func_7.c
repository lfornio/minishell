/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 14:48:43 by lfornio           #+#    #+#             */
/*   Updated: 2021/12/24 14:01:09 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *delete_space(char *str) // удаляем пробелы в начала и конце строки
{
	char *s = NULL;
	int len;
	len = ft_strlen(str);

	if(str[0] == ' ')
		s = ft_substr(str, 1, len - 1);
	else if(str[0] == ' ' && str[len - 1] == ' ')
		s = ft_substr(str, 1, len - 2);
	else if(str[len - 1] == ' ')
		s = ft_substr(str, 0, len - 1);
	else
		return (str);
	free(str);
	return(s);

}


void removing_spaces_at_the_beginning_and_end_in_str(t_prepars *list)  //ищем узлы-строки без пайпов
{
	t_prepars *p;
	p = list;
	while(p)
	{
		if(p->str[0] != '|')
			p->str = delete_space(p->str);
		p = p->next;
	}
}



int count_pipes(t_prepars *list)  // считаем сколько пайпов
{
	t_prepars *p;
	p = list;
	int count;
	count = 0;
	while(p)
	{
		if (p->str[0] == '|')
			count++;
		p = p->next;
	}
	return(count);
}

void delete_node_with_pipe(t_prepars *list)  //удаляем узлы с пайпами
{
	t_prepars *p;
	p = list;
	while(p)
	{
		if(p->str[0] == '|')
		{
			p = delete_node_prepars(p, list);
			continue;
		}
		 p = p->next;
	}

}
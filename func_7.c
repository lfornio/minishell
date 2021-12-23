/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 14:48:43 by lfornio           #+#    #+#             */
/*   Updated: 2021/12/23 16:13:32 by lfornio          ###   ########.fr       */
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

void delete_last_node(t_prepars *p, t_prepars *head)
{
	t_prepars *tmp;
	tmp = head;
	while(tmp->next != p)
	{
		tmp = tmp->next;
	}
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

int count_pipes(t_prepars *list)
{
	t_prepars *p = list;
	t_prepars *tmp;
	int size;
	size = size_list_prepars(p);
	char *s;
	s = get_str_from_list(p, size);
	tmp = get_ptr_from_list(p, size);
	if(ft_strlen(s) == 0)
		delete_last_node(tmp, list);





	return(size);


}

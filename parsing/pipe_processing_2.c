/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_processing_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 19:08:51 by lfornio           #+#    #+#             */
/*   Updated: 2022/02/02 16:48:39 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
удаляем узлы с пайпами
*/
void	delete_node_with_pipe(t_prepars *list)
{
	t_prepars	*p;

	p = list;
	while (p)
	{
		if (p->str[0] == '|')
		{
			p = delete_node_prepars(p, list);
			continue ;
		}
		p = p->next;
	}
}

/*
функция берет указатель по индексу в списке
*/
t_prepars	*get_ptr_from_list(t_prepars *list, int index)
{
	t_prepars	*p;
	int			i;

	i = 1;
	p = list;
	while (i < index)
	{
		p = p->next;
		i++;
	}
	return (p);
}

/*
если последний узел пустой - удаляет, если пайп - ошибка
*/
int	error_last_pipe(t_prepars *list)
{
	t_prepars	*p;
	t_prepars	*tmp;
	int			size;
	char		*s;

	p = list;
	size = size_list_prepars(p);
	s = get_str_from_list(p, size);
	tmp = get_ptr_from_list(p, size);
	if (ft_strlen(s) == 0)
		delete_last_node_prepars(tmp, list);
	size = size_list_prepars(p);
	s = get_str_from_list(p, size);
	if (ft_strncmp(s, "|", 1) == 0)
		return (print_error_for_quotes());
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 11:10:40 by lfornio           #+#    #+#             */
/*   Updated: 2022/01/15 14:19:15 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int error_pipe_found(char *str, int i, int count) // щшибка пайпа
{
	if (count == 0 && (i == 0 || i == 1) && str[i] == '|')
		return (print_error_token("|"));
	i++;
	if (str[i] && str[i] == '|')
		return (print_error_token("|"));
	else if (str[i] && str[i] == ' ')
	{
		i++;
		if (str[i] && str[i] == '|')
			return (print_error_token("|"));
	}
	return (0);
}

t_prepars *write_pipe_private_node(t_prepars *q, int *i, int a)
{
	// t_prepars *tmp;
	char *s;
	char *s2;

	// tmp = q;
	s = ft_strdup(q->str);
	free(q->str);
	q->str = ft_substr(s, *i - a, a);
	q = a_new_node_in_the_middle(q, "|");
	s2 = ft_substr(s, *i + 1, ft_strlen(s) - a - 1);
	q = a_new_node_in_the_middle(q, s2);
	free(s);
	free(s2);
	return(q);
}

t_prepars *remake_list_with_pipes(char *str, int count, t_prepars *p) // если нашли | то перезаписываем список
{
	t_prepars *q;
	int i;
	int a;

	i = -1;
	a = 0;
	q = p;
	while (str[++i])
	{
		if (str[i] == '|')
		{
			if (error_pipe_found(str, i, count) < 0)
			{
				return (NULL);
		}
			else
			{
				q = write_pipe_private_node(q, &i, a);
				break;
			}
		}
		a++;
	}
	return (q);
}

int search_for_pipes(t_prepars *list) // ищет пайпы и презаписывает список в строках без ' "
{
	t_prepars *p;
	int count_node;

	p = list;
	count_node = 0;
	while (p)
	{
		if (p->str[0] != '\'' && p->str[0] != '\"' && found_char_c(p->str, '|'))
		{
			p = remake_list_with_pipes(p->str, count_node, p);
			if (!p)
				return (-1);
			continue;
		}
		count_node++;
		p = p->next;
	}
	return (0);
}

int error_last_pipe(t_prepars *list) // если последний узел пустой - удаляет, если пайп - ошибка
{
	t_prepars *p;
	t_prepars *tmp;
	int size;
	char *s;

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

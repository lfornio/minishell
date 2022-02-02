/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_processing_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 11:10:40 by lfornio           #+#    #+#             */
/*   Updated: 2022/02/02 11:07:04 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
ошибка пайпа
*/
int	error_pipe_found(char *str, int i, int count)
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

t_prepars	*write_pipe_private_node(t_prepars *q, int *i, int a)
{
	char	*s;
	char	*s2;

	s = ft_strdup(q->str);
	free(q->str);
	q->str = ft_substr(s, *i - a, a);
	q = a_new_node_in_the_middle(q, "|");
	s2 = ft_substr(s, *i + 1, ft_strlen(s) - a - 1);
	q = a_new_node_in_the_middle(q, s2);
	free(s);
	free(s2);
	return (q);
}

/*
если нашли | то перезаписываем список
*/
t_prepars	*remake_list_with_pipes(char *str, int count, t_prepars *p)
{
	t_prepars	*q;
	int			i;
	int			a;

	i = -1;
	a = 0;
	q = p;
	while (str[++i])
	{
		if (str[i] == '|')
		{
			if (error_pipe_found(str, i, count) < 0)
				return (NULL);
			else
			{
				q = write_pipe_private_node(q, &i, a);
				break ;
			}
		}
		a++;
	}
	return (q);
}

/*
ищем с
*/
int	found_char_c(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/*
ищет пайпы и презаписывает список в строках без ' "
*/
int	search_for_pipes(t_prepars *list)
{
	t_prepars	*p;
	int			count_node;

	p = list;
	count_node = 0;
	while (p)
	{
		if (p->str[0] != '\'' && p->str[0] != '\"' && found_char_c(p->str, '|'))
		{
			p = remake_list_with_pipes(p->str, count_node, p);
			if (!p)
				return (-1);
			continue ;
		}
		count_node++;
		p = p->next;
	}
	return (0);
}

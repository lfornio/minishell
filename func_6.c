/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 11:10:40 by lfornio           #+#    #+#             */
/*   Updated: 2021/12/24 11:29:47 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int error_pipe_found(char *str, int i, int count) // щшибка пайпа
{
	if (count == 0 && (i == 0 || i == 1) && str[i] == '|')
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	i++;
	if (str[i] && str[i] == '|')
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	else if (str[i] && str[i] == ' ')
	{
		i++;
		if (str[i] && str[i] == '|')
		{
			{
				printf("minishell: syntax error near unexpected token `|'\n");
				return (1);
			}
		}
	}
	return (0);
}

t_prepars *a_new_node_in_the_middle(t_prepars *middle, char *str) //добавляем новый узел в середину
{
	t_prepars *new;
	t_prepars *tmp;
	new = malloc(sizeof(t_prepars));
	if (!new)
		return (NULL);
	tmp = middle->next;
	middle->next = new;
	new->str = ft_strdup(str);
	new->next = tmp;
	return (new);
}
// t_prepars *split_command(char **tab, t_prepars *p, t_prepars *head)
// {
// 	printf("1\n");
// 	print_list_prepars(head);
// 	int i;
// 	i = 0;
// 	free(p->str);
// 	p->str = ft_strdup(tab[0]);
// 	p = a_new_node_in_the_middle(p, "|");
// 	p = a_new_node_in_the_middle(p, tab[1]);

// 	free(tab);
// 	printf("2\n");
// 	print_list_prepars(head);
// 	return (p);
// }

t_prepars *search(char *str, int count, t_prepars *p) // если нашли | то перезаписываем список
{
	int i;
	i = 0;
	t_prepars *q;
	q = p;
	int a;
	a = 0;
	char *s;
	char *s2;
	while (str[i])
	{

		if (str[i] == '|')
		{
			if (error_pipe_found(str, i, count))
				exit(1);
			else
			{
				s = ft_strdup(q->str);
				free(q->str);
				q->str = ft_substr(s, i - a, a);
				q = a_new_node_in_the_middle(q, "|");

				s2 = ft_substr(s, i + 1, ft_strlen(s) - a - 1);
				q = a_new_node_in_the_middle(q, s2);
				free(s);
				free(s2);
				return(q);
			}
		}
		a++;
		i++;
	}

	return (NULL);
}
int found_char_c(char *str, char c) //ищем с
{
	int i;
	i = 0;
	while(str[i])
	{
		if(str[i] == c)
			return (1);
		i++;
	}
	return(0);
}

void search_for_commands(t_prepars *list)  // ищет пайпы и презаписывает список в строках без ' "
{
	t_prepars *p;
	p = list;
	int count_node;
	count_node = 0;

	while (p)
	{
		if (p->str[0] != '\'' && p->str[0] != '\"' && found_char_c(p->str, '|'))
		{

			p = search(p->str, count_node, p);
			continue;
		}
		count_node++;
		p = p->next;
	}
}

void delete_last_node(t_prepars *p, t_prepars *head)  // удаляет последний узел в списке
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
void error_last_pipe(t_prepars *list)   // если последний узел пустой - удаляет, если пайп - ошибка
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
	size = size_list_prepars(p);
	s = get_str_from_list(p, size);
	if(ft_strncmp(s, "|", 1) == 0)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		exit(1);
	}

}



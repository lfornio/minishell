/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepars_list_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 19:20:06 by lfornio           #+#    #+#             */
/*   Updated: 2022/02/02 16:50:32 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
чистит список препарса
*/
void	free_list_prepars(t_prepars **list)
{
	t_prepars	*p;

	p = NULL;
	if (!*list)
		return ;
	while (*list)
	{
		p = *list;
		*list = (*list)->next;
		if (p->str)
			free(p->str);
		free(p);
	}
}

/*
печатает список препарса
*/
void	print_list_prepars(t_prepars *list)
{
	t_prepars	*p;

	p = list;
	while (p != NULL)
	{
		printf("%s\n", p->str);
		p = p->next;
	}
}

/*
функция берет строку по индексу в списке
*/
char	*get_str_from_list(t_prepars *list, int index)
{
	t_prepars	*p;
	int			i;
	char		*str;

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

/*
функция считает размер списка препарса
*/
int	size_list_prepars(t_prepars *list)
{
	int	count;

	count = 0;
	if (!list)
		return (-1);
	while (list)
	{
		count++;
		list = list->next;
	}
	return (count);
}

/*
список препарса записывает в массив строк
*/
char	**prepars_list_remake_arr(t_prepars *list)
{
	char	**tab;
	int		size_list;
	int		i;

	i = 0;
	size_list = size_list_prepars(list);
	tab = (char **)malloc(sizeof(char *) * (size_list + 1));
	if (!tab)
		return (NULL);
	while (list)
	{
		tab[i] = ft_strdup(list->str);
		i++;
		list = list->next;
	}
	tab[i] = NULL;
	return (tab);
}

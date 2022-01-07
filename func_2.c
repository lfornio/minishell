/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 11:14:03 by lfornio           #+#    #+#             */
/*   Updated: 2022/01/07 11:36:43 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



char *ft_quote(char *str, int *i, char c) // функция обрабатывает  ' и " в строке
{
	int a;
	a = *i;
	(*i)++;
	int count;
	count = 1;
	char *tmp;
	while (str[*i])
	{
		if (str[*i] == c)
			break;
		count++;
		(*i)++;
	}
	if (str[*i] == c)
		count++;
	tmp = ft_substr(str, a, count);
	return (tmp);
}

char *ft_non(char *str, int *i)    //функция обрабатывает символы отличные от  ' "
{
	int a;
	int count;
	char *tmp;

	a = *i;
	count = 0;
	while (str[*i] && str[*i] != '\'' && str[*i] != '\"')
	{
		count++;
		(*i)++;
	}
	(*i)--;
	tmp = ft_substr(str, a, count);
	return (tmp);
}

t_prepars *preparsing_str(char *str)   //функция делить строку на список разделенный на "" ''  символы
{
	int i = 0;
	char *tmp;
	int j = 0;
	t_prepars *prepars_list = NULL;

	while (str[i])
	{
		if (str[i] == '\'')
			tmp = ft_quote(str, &i, '\'');
		else if (str[i] == '\"')
			tmp = ft_quote(str, &i, '\"');
		else
			tmp = ft_non(str, &i);
		if(!tmp)
			return (NULL);
		if (j == 0)
			push_node_prepars(&prepars_list, tmp);
		else
			push_last_node_prepars(&prepars_list, tmp);
		free(tmp);
		j++;
		i++;
	}
	return (prepars_list);
}

int size_list_prepars(t_prepars *list)  //функция считает размер списка препарса
{
	int count;
	count = 0;

	if(!list)
		return(-1);
	while(list)
	{
		count++;
		list = list->next;
	}
	return(count);

}

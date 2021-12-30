/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_11.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 10:10:45 by lfornio           #+#    #+#             */
/*   Updated: 2021/12/29 16:08:27 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **prepars_list_remake_arr(t_prepars *list)  //список препарса записывает в массив строк
{
	int size_list;
	size_list = size_list_prepars(list);
	char **tab;
	tab = (char **)malloc(sizeof(char *) * (size_list + 1));
	if (!tab)
		return (NULL);
	int i = 0;

	while (list)
	{

		tab[i] = ft_strdup(list->str);
		i++;
		list = list->next;
	}
	tab[i] =  NULL;
	return(tab);
}


char **split_str_whitespace(char *str, t_data *data) //делит строку пробелом не в кавычках на массив строк
{

	char *copy;
	copy = ft_strdup(str);
	int i;
	i = 0;
	while (copy[i])
	{
		if(copy[i] == '\'')
			skip_the_quotes(copy, &i, '\'');
		if (copy[i] == '$')
		{
			i++;
			if(!copy[i])
				break;
			else
				copy = processing_the_dollar(copy, &i, data);
		}
		i++;
	}
	t_prepars *split_whitespace = NULL;
	i = 0;
	int flag;
	flag = 0;
	int a;
	a = 0;
	char *s;
	while (copy[i])
	{
		if (copy[i] == '\'')
			skip_the_quotes(copy, &i, '\'');
		else if (copy[i] == '\"')
			skip_the_quotes(copy, &i, '\"');
		else if (copy[i] == ' ')
		{
			if (flag == 0)
			{
				s = ft_substr(copy, 0, i);
				push_node_prepars(&split_whitespace, s);
				flag++;
				a = i + 1;
			}
			else
			{
				s = ft_substr(copy, a, i - a);
				push_last_node_prepars(&split_whitespace, s);
				a = i + 1;
			}
			free(s);
		}

		i++;
	}
	// printf("copy = %s\n", copy);
	if (!copy[i])
	{
		s = ft_substr(copy, a, i - a);
		if (flag == 0)
		{
			push_node_prepars(&split_whitespace, s);
			flag++;
		}
		else
			push_last_node_prepars(&split_whitespace, s);
		free(s);

	}

	// print_list_prepars(split_whitespace);
	// printf("+++++++++++++++++++++++\n");
	// tab = ft_split(str, ' ');
	free(copy);
	t_prepars *ptr;
	ptr = split_whitespace;
	char *tmp = NULL;

	i = 0;
	while (ptr)
	{
		tmp = ft_strdup(ptr->str);
		i = 0;
		while(tmp[i])
		{
			if(tmp[i] == '\'')
				tmp = removing_the_quotes(tmp, &i, '\'');
			else if(tmp[i] == '\"')
				tmp = removing_the_quotes(tmp, &i, '\"');
			i++;
		}
		free(ptr->str);
		ptr->str = ft_strdup(tmp);
		ptr = ptr->next;
		free(tmp);
	}
	// print_list_prepars(split_whitespace);
	char **tab = NULL;
	tab = prepars_list_remake_arr(split_whitespace);
	free_list_prepars(&split_whitespace);
	return (tab);
}

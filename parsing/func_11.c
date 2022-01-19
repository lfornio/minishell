/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_11.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 10:10:45 by lfornio           #+#    #+#             */
/*   Updated: 2022/01/18 20:07:02 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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



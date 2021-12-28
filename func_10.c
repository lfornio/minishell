/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_10.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 12:08:56 by lfornio           #+#    #+#             */
/*   Updated: 2021/12/26 16:57:14 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int size_list_envp(t_list *list) //функция считает размер списка envp
{
	int count;
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

t_list *get_envp_list(char **envp) //	считываем окружение и сохраняем в список
{
	t_list *envp_list = NULL;
	int i = 0;
	push_node(&envp_list, envp[i]);
	i++;
	while (envp[i])
	{
		push_last_node(&envp_list, envp[i]);
		i++;
	}
	return (envp_list);
}

char **envp_list_remake_arr(t_list *list)  //список envp записывает в массив строк
{
	int size_envp;
	size_envp = size_list_envp(list);
	char **tab;
	tab = (char **)malloc(sizeof(char *) * (size_envp + 1));
	if (!tab)
		return (NULL);
	int i = 0;
	char *tmp1;
	char *tmp2;

	while (list)
	{
		tmp1 = ft_strjoin(list->key, "=");
		tmp2 = ft_strjoin(tmp1, list->value);
		free(tmp1);
		tab[i] = tmp2;
		i++;
		list = list->next;
	}
	tab[i] =  NULL;
	// for (int i = 0; tab[i]; i++)
	// 	printf("%s\n", tab[i]);
	return(tab);
}

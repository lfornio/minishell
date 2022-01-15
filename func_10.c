/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_10.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 12:08:56 by lfornio           #+#    #+#             */
/*   Updated: 2022/01/15 15:36:06 by lfornio          ###   ########.fr       */
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

char **envp_list_remake_arr(t_list *list) //список envp записывает в массив строк
{
	char **tab;
	int i;
	char *tmp1;
	char *tmp2;

	i = 0;
	tab = (char **)malloc(sizeof(char *) * (size_list_envp(list) + 1));
	if (!tab)
		return (NULL);
	while (list)
	{
		tmp1 = ft_strjoin(list->key, "=");
		tmp2 = ft_strjoin(tmp1, list->value);
		free(tmp1);
		tab[i] = tmp2;
		i++;
		list = list->next;
	}
	tab[i] = NULL;
	return (tab);
}

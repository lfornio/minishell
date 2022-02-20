/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 12:08:56 by lfornio           #+#    #+#             */
/*   Updated: 2022/02/20 17:01:40 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
функция считает размер списка envp
*/
int	size_list_envp(t_list *list)
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
список envp записывает в массив строк
*/
char	**envp_list_remake_arr(t_list *list)
{
	char	**tab;
	int		i;
	char	*tmp1;
	char	*tmp2;

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

/*
печатает список env
*/
void	print_envp_list(t_list **list)
{
	t_list	*p;

	p = *list;
	while (p != NULL)
	{
		printf("%s=%s\n", p->key, p->value);
		p = p->next;
	}
}

void	free_arr_envp(t_envp *p)
{
	int	i;

	i = 0;
	while (p->arr_envp[i])
	{
		free(p->arr_envp[i]);
		i++;
	}
}

void	free_env_struct(t_envp *env)
{
	if (env->arr_envp)
	{
		free_arr_envp(env);
		free(env->arr_envp);
		env->arr_envp = NULL;
	}
	if (env->envp_list)
		free_list(&env->envp_list);
	if (env->envp_list_sort)
		free_list(&env->envp_list_sort);
}

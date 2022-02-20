/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 19:41:16 by lfornio           #+#    #+#             */
/*   Updated: 2022/02/20 17:00:08 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
функция парсит строку из envp на массив строк:
tab[0] - ключ(до =), tab[1] - значение(после =)
и записывает в узел
*/
void	pars_envp_str(t_list *list, char *str)
{
	char	**tab;

	tab = ft_split(str, '=');
	list->key = tab[0];
	list->value = tab[1];
	free(tab);
}

void	push_first_node_envp(t_list **list, char *str)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return ;
	pars_envp_str(new, str);
	new->next = *list;
	*list = new;
}

void	push_last_node_envp(t_list **list, char *str)
{
	t_list	*tmp;
	t_list	*new;

	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	new = malloc(sizeof(t_list));
	if (!new)
		return ;
	pars_envp_str(new, str);
	new->next = NULL;
	tmp->next = new;
}

/*
считываем окружение и сохраняем в список
*/
t_list	*get_envp_list(char **envp)
{
	t_list	*envp_list;
	int		i;

	i = 0;
	envp_list = NULL;
	push_first_node_envp(&envp_list, envp[i]);
	i++;
	while (envp[i])
	{
		push_last_node_envp(&envp_list, envp[i]);
		i++;
	}
	return (envp_list);
}

void	init_env(t_envp *env_struct, char **envp)
{
	env_struct->envp_list = get_envp_list(envp);
	env_struct->envp_list_sort = get_envp_list(envp);
	env_struct->arr_envp = envp_list_remake_arr(env_struct->envp_list);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 19:41:16 by lfornio           #+#    #+#             */
/*   Updated: 2022/01/18 19:52:41 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
считываем окружение и сохраняем в список
*/
t_list	*get_envp_list(char **envp)
{
	t_list	*envp_list;
	int		i;

	i = 0;
	envp_list = NULL;
	push_node(&envp_list, envp[i]);
	i++;
	while (envp[i])
	{
		push_last_node(&envp_list, envp[i]);
		i++;
	}
	return (envp_list);
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

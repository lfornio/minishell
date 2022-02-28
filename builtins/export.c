/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 11:53:27 by mshad             #+#    #+#             */
/*   Updated: 2022/02/24 11:10:13 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	sort_swap(t_list *ptr, t_list *ptr2, t_list *tmp)
{
	tmp->key = ptr->key;
	tmp->value = ptr->value;
	ptr->key = ptr2->key;
	ptr->value = ptr2->value;
	ptr2->key = tmp->key;
	ptr2->value = tmp->value;
}

static void	sort_list(t_envp *envp_struct)
{
	int		did_swap;
	t_list	*ptr;
	t_list	*tmp;

	tmp = malloc(sizeof(t_list));
	did_swap = 1;
	while (did_swap)
	{
		did_swap = 0;
		ptr = envp_struct->envp_list_sort;
		while (ptr->next)
		{
			if (ft_strcmp(ptr->key, ptr->next->key) > 0)
			{
				sort_swap(ptr, ptr->next, tmp);
				did_swap = 1;
			}
			ptr = ptr->next;
		}
	}
	free(tmp);
}

static void	print_export(int out, t_envp *envp_struct)
{
	t_list	*ptr;

	ptr = envp_struct->envp_list_sort;
	while (ptr)
	{
		ft_putstr_fd("declare -x ", out);
		ft_putstr_fd(ptr->key, out);
		if (ptr->value)
		{
			ft_putstr_fd("=\"", out);
			ft_putstr_fd(ptr->value, out);
			ft_putchar_fd('"', out);
		}
		ft_putchar_fd('\n', out);
		ptr = ptr->next;
	}
}

char	**envp_list_arr(t_list *list)
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
		if (list->value == NULL)
		{
			list = list->next;
			continue ;
		}
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

void	ft_export(t_data *data, int out, t_envp *envp_struct)
{
	int		i;

	g_status = 0;
	if (!data->commands->tab_cmd[1])
	{
		sort_list(envp_struct);
		print_export(out, envp_struct);
		return ;
	}
	else
	{
		i = 1;
		while (data->commands->tab_cmd[i])
		{
			if (key_validation("export", data->commands->tab_cmd[i]) == 0)
			{
				change_key_value(envp_struct, data->commands->tab_cmd[i]);
				free_arr_envp(envp_struct);
				free(envp_struct->arr_envp);
				envp_struct->arr_envp = envp_list_arr(envp_struct->envp_list);
			}
			i++;
		}
	}
}

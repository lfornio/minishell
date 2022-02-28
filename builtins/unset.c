/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:43:27 by mshad             #+#    #+#             */
/*   Updated: 2022/02/24 11:32:44 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_list	*delete_from_list(t_list **lst, t_list *ptr)
{
	t_list	*elem;
	t_list	*curr;

	elem = NULL;
	curr = *lst;
	if (curr && curr == ptr)
	{
		elem = curr;
		*lst = elem->next;
		elem->next = NULL;
		return (elem);
	}
	while (curr->next)
	{
		if (curr->next == ptr)
		{
			elem = curr->next;
			curr->next = curr->next->next;
			elem->next = NULL;
			break ;
		}
		curr = curr->next;
	}
	return (elem);
}

t_list	*find_env_key(t_list *envp_list, char *arg)
{
	t_list	*ptr;
	char	*tmp_key;

	tmp_key = find_key_arg(arg, '=');
	if (!tmp_key)
		return (NULL);
	ptr = envp_list;
	while (ptr)
	{
		if (ft_strcmp(ptr->key, tmp_key) == 0)
		{
			free(tmp_key);
			return (ptr);
		}
		ptr = ptr->next;
	}
	free(tmp_key);
	return (NULL);
}

static void	ft_unset2(t_data *data, t_list *envp_list)
{
	int		i;
	t_list	*ptr;
	t_list	*tmp;

	i = 1;
	while (data->commands->tab_cmd[i])
	{
		ptr = find_env_key(envp_list, data->commands->tab_cmd[i]);
		if (!key_validation("unset", data->commands->tab_cmd[i]) && ptr)
		{
			tmp = delete_from_list(&envp_list, ptr);
			free(tmp->key);
			if (tmp->value)
				free(tmp->value);
			free(tmp);
		}
		i++;
	}
}

void	ft_unset(t_data *data, t_envp *envp_struct)
{
	g_status = 0;
	if (!data->commands->argument)
		return ;
	ft_unset2(data, envp_struct->envp_list);
	ft_unset2(data, envp_struct->envp_list_sort);
	free_arr_envp(envp_struct);
	free(envp_struct->arr_envp);
	envp_struct->arr_envp = envp_list_arr(envp_struct->envp_list);
}

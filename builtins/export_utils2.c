/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_export_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshad <mshad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 10:53:17 by mshad             #+#    #+#             */
/*   Updated: 2022/02/26 12:41:00 by mshad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_key_arg(char *s, int c)
{
	int		i;
	char	*str;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	if (s[i] == '\0')
		return (ft_strdup(s));
	str = malloc(sizeof(char) * i + 1);
	malloc_error(str);
	i = 0;
	while (s[i] != c)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*find_value_arg(char *s, int c)
{
	int		i;
	char	*str;

	str = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
		{
			str = ft_strdup((char *)s + i + 1);
			break ;
		}
		else
			i++;
	}
	if (c == '\0')
		str = ft_strdup((char *)s + ft_strlen(s));
	return (str);
}

static void	update_list_env(t_list *en, char *arg_key, char *arg_value)
{
	while (1)
	{
		if (ft_strcmp(en->key, arg_key) == 0)
		{
			if (arg_value)
			{
				free(en->value);
				en->value = ft_strdup(arg_value);
			}
			break ;
		}
		if (en->next == NULL)
		{
			en->next = malloc(sizeof(t_list));
			en->next->key = ft_strdup(arg_key);
			if (arg_value)
				en->next->value = ft_strdup(arg_value);
			else
				en->next->value = NULL;
			en->next->next = NULL;
			break ;
		}
		en = en->next;
	}
}

void	change_key_value(t_envp *envp_struct, char *args)
{
	t_list	*head;
	t_list	*head_sort;
	char	*arg_key;
	char	*arg_value;

	arg_key = find_key_arg(args, '=');
	arg_value = find_value_arg(args, '=');
	head = envp_struct->envp_list;
	head_sort = envp_struct->envp_list_sort;
	update_list_env(head, arg_key, arg_value);
	envp_struct->envp_list = head;
	update_list_env(head_sort, arg_key, arg_value);
	envp_struct->envp_list_sort = head_sort;
	free(arg_key);
	free(arg_value);
}

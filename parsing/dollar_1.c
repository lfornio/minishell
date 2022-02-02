/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 10:43:09 by lfornio           #+#    #+#             */
/*   Updated: 2022/02/01 14:43:56 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*change_dollar(char *str, t_data *data)
{
	t_list	*p;
	int		len;

	p = data->envp_list;
	len = (int)ft_strlen(str);
	while (p)
	{
		if (((int)ft_strlen(p->key) == len) && !ft_strncmp(str, p->key, len))
			return (p->value);
		p = p->next;
	}
	return (NULL);
}

char	*get_dollar_value(char *str, int a, int count, t_data *data)
{
	char	*key;
	char	*value;

	key = ft_substr(str, a, count);
	value = change_dollar(key, data);
	free(key);
	return (value);
}

int	count_char_for_dollar(char *str, int *i, int a)
{
	int	count;

	count = 0;
	while (str[*i])
	{
		if (str[a] == '?' || ft_isdigit(str[a]))
		{
			(*i)++;
			break ;
		}
		else if (ft_isalnum(str[*i]) || str[*i] == '_')
			count++;
		else
			break ;
		(*i)++;
	}
	return (count);
}

void	init_dollar_struct(t_dollar *dollar)
{
	dollar->after = NULL;
	dollar->before = NULL;
	dollar->value = NULL;
	dollar->tmp = NULL;
}

char	*processing_the_dollar(char *str, int *i, t_data *data)
{
	char		*res;
	int			a;
	int			count;
	t_dollar	dollar;

	a = *i;
	init_dollar_struct(&dollar);
	dollar.before = ft_substr(str, 0, (*i) - 1);
	if (str[a] == ' ')
	{
		free(dollar.before);
		return (str);
	}
	count = count_char_for_dollar(str, i, a);
	if (count)
		dollar.value = get_dollar_value(str, a, count, data);
	dollar.after = ft_substr(str, (*i), (int)ft_strlen(str));
	res = get_change_str_without_dollar(&dollar, str[a], i);
	free(str);
	return (res);
}

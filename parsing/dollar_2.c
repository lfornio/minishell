/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 10:27:41 by lfornio           #+#    #+#             */
/*   Updated: 2022/02/20 16:16:41 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*removing_the_dollar_before_quotes(char *str, int *i)
{
	char	*before;
	char	*after;
	char	*tmp;

	before = ft_substr(str, 0, (*i) - 1);
	if (ft_isdigit(str[*i]))
		after = ft_substr(str, (*i) + 1, ft_strlen(str) - (*i));
	else
		after = ft_substr(str, (*i), ft_strlen(str) - (*i));
	tmp = ft_strjoin(before, after);
	free(before);
	free(after);
	free(str);
	(*i) -= 2;
	return (tmp);
}

char	*remov_quote_in_str_with_dollar(int count, char *str, int *i,
	char *before)
{
	char	*after;
	char	*tmp;
	char	*tmp1;
	char	*res;

	after = ft_substr(str, (*i) + 1, ft_strlen(str) - (*i));
	if (count)
	{
		tmp = ft_substr(str, (*i) - count, count);
		tmp1 = ft_strjoin(before, tmp);
		(*i) = ft_strlen(tmp1);
		free(tmp);
		free(before);
		res = ft_strjoin(tmp1, after);
		free(tmp1);
		free(after);
	}
	else
	{
		res = ft_strjoin(before, after);
		(*i) = ft_strlen(before);
		free(before);
		free(after);
	}
	return (res);
}

char	*removing_the_quotes(char *str, int *i, char c)
{
	char	*before;
	char	*res;
	int		count;

	count = 0;
	before = ft_substr(str, 0, (*i));
	(*i)++;
	while (str[*i])
	{
		if (str[*i] == c)
			break ;
		count++;
		(*i)++;
	}
	res = remov_quote_in_str_with_dollar(count, str, i, before);
	free(str);
	(*i)--;
	return (res);
}

char	*removing_the_double_quotes_with_dollar(char *copy, int *i, int *a,
	t_envp *env)
{
	(*i)++;
	while (copy[*i])
	{
		if (copy[*i] == '$')
		{
			if (copy[(*i) + 1] && copy[(*i) + 1] == '\"')
			{
				copy = removing_the_quotes(copy, a, '\"');
				(*i)--;
				return (copy);
			}
			copy = after_dollar_char(copy, i, env);
		}
		else if (copy[*i] == '\"')
			break ;
		(*i)++;
	}
	(*i) -= 2;
	copy = removing_the_quotes(copy, a, '\"');
	return (copy);
}

char	*removing_the_double_quotes(char *str, int *i, t_envp *env)
{
	int		a;
	char	*copy;

	a = *i;
	copy = ft_strdup(str);
	copy = removing_the_double_quotes_with_dollar(copy, i, &a, env);
	free(str);
	return (copy);
}

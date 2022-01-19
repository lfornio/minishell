/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:50:21 by lfornio           #+#    #+#             */
/*   Updated: 2022/01/19 11:14:36 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
пропускаем кавычки
*/
void	skip_the_quotes(char *str, int *i, char c)
{
	(*i)++;
	while (str[*i])
	{
		if (str[*i] == c)
			return ;
		(*i)++;
	}
}

/*
функция обрабатывает  ' и " в строке
*/
char	*ft_quote(char *str, int *i, char c)
{
	int		a;
	int		count;
	char	*tmp;

	a = *i;
	(*i)++;
	count = 1;
	while (str[*i])
	{
		if (str[*i] == c)
			break ;
		count++;
		(*i)++;
	}
	if (str[*i] == c)
		count++;
	tmp = ft_substr(str, a, count);
	return (tmp);
}

/*
функция обрабатывает символы отличные от  ' "
*/
char	*ft_non(char *str, int *i)
{
	int		a;
	int		count;
	char	*tmp;

	a = *i;
	count = 0;
	while (str[*i] && str[*i] != '\'' && str[*i] != '\"')
	{
		count++;
		(*i)++;
	}
	(*i)--;
	tmp = ft_substr(str, a, count);
	return (tmp);
}

/*
функция находит кавычки
*/
char	*processing_quote(char *str, int *i)
{
	char	*tmp;

	if (str[*i] == '\'')
		tmp = ft_quote(str, i, '\'');
	else if (str[*i] == '\"')
		tmp = ft_quote(str, i, '\"');
	else
		tmp = ft_non(str, i);
	return (tmp);
}

void	remove_quote(t_prepars **list)
{
	t_prepars	*p;
	char		*tmp;
	int			i;

	p = *list;
	tmp = NULL;
	i = 0;
	while (p)
	{
		tmp = ft_strdup(p->str);
		i = 0;
		while (tmp[i])
		{
			if (tmp[i] == '\'')
				tmp = removing_the_quotes(tmp, &i, '\'');
			else if (tmp[i] == '\"')
				tmp = removing_the_quotes(tmp, &i, '\"');
			i++;
		}
		free(p->str);
		p->str = ft_strdup(tmp);
		p = p->next;
		free(tmp);
	}
}

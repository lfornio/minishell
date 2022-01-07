/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 10:09:51 by lfornio           #+#    #+#             */
/*   Updated: 2022/01/07 11:03:03 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_spaces_and_tabs(char *str, int *i)  //посчитали сколько надо убрать символов из страрой строки чтобы посчитать malloc для новой
{
	int count;
	int a;

	count = 0;
	a = *i;
	(*i)++;
	while(str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
	{
		count++;
		(*i)++;
	}
	return(count);
}

void skipping_space(char *str, int *i)  //пропустили в строке пробелы и табуляции
{
	(*i)++;
	while(str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
}

char	*copy_str_without_extra_spaces(char *str, int count)
{
	char	*tmp;
	int		len;
	int		i;
	int		j;

	i = -1;
	j = 0;
	len = ft_strlen(str);
	tmp = malloc(sizeof(char) * (len - count + 1));
	if (!tmp)
		return (NULL);
	while (str[++i])
	{
		if (str[i] == ' ' || str[i] == '\t')
		{
			tmp[j++] = ' ';
			skipping_space(str, &i);
		}
		tmp[j++] = str[i];
	}
	tmp[j] = '\0';
	free (str);
	return (tmp);
}

char *remove_extra_spaces_and_tabs_in_str(char *str)   //убрали из строки лишние пробелы и табуляции
{
	int i;
	int count;
	char *tmp;

	i = -1;
	count = 0;
	while(str[++i])
	{
		if(str[i] == ' ' || str[i] == '\t')
			count += count_spaces_and_tabs(str, &i);
	}
	tmp = copy_str_without_extra_spaces(str, count);
	return(tmp);
}

void removing_spaces_and_tabs_in_list(t_prepars *list)   //перезаписали список без пробелов и табуляций
{
	t_prepars *p;

	p = list;
	while(p)
	{
		if(p->str[0] != '\'' && p->str[0] != '\"')
			p->str = remove_extra_spaces_and_tabs_in_str(p->str);
		p = p->next;
	}
}

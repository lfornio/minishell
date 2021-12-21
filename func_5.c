/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 10:09:51 by lfornio           #+#    #+#             */
/*   Updated: 2021/12/19 11:03:34 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_spaces_and_tabs(char *str, int *i)  //посчитали сколько надо убрать символов из страрой строки чтобы посчитать malloc для новой
{
	int count;
	count = 0;
	int a;
	a = *i;
	(*i)++;

	while(str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
	{
		count++;
		(*i)++;
	}
	return(count);
}

void skipping(char *str, int *i)  //пропустили в строке пробелы и табуляции
{
	(*i)++;

	while(str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
	{
		(*i)++;
	}
}

char *remov(char *str)   //убрали из строки лишние пробелы и табуляции
{
	int i;
	i = 0;
	int count;
	count = 0;
	int len;
	len = ft_strlen(str);

	while(str[i])
	{
		if(str[i] == ' ' || str[i] == '\t')
			count += count_spaces_and_tabs(str, &i);
		i++;
	}
	char *tmp;
	tmp = malloc(sizeof(char) * (len - count + 1));
	if(!tmp)
	{
		printf("Error malloc\n");
		exit(1);
	}
	int j;
	j = 0;
	i = 0;
	while(str[i])
	{
		if(str[i] == ' ' || str[i] == '\t')
		{
			tmp[j] = ' ';
			j++;
			skipping(str, &i);
		}
		tmp[j] = str[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	free(str);
	return(tmp);
}

void removing_spaces_and_tabs(t_prepars *list)   //перезаписали список без пробелов и табуляций
{
	t_prepars *p;
	p = list;
	while(p)
	{
		if(p->str[0] != '\'' && p->str[0] != '\"')
			p->str = remov(p->str);
		p = p->next;
	}
}

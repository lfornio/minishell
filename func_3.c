/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 08:38:00 by lfornio           #+#    #+#             */
/*   Updated: 2021/12/25 10:24:45 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int error_prepars_quote(char *str, char c)   //не закрытые кавычки
{
	int len;
	len = ft_strlen(str);
	if (len == 1 || str[len - 1] != c)
		return (1);
	return (0);
}

void error_prepars_str(t_prepars *prepars_list, char *line) // выход из программы при наличии незакрытых кавычек
{
	t_prepars *list;
	list = prepars_list;

	while (prepars_list)
	{
		if (prepars_list->str[0] == '\'')
		{
			if (error_prepars_quote(prepars_list->str, '\''))
			{
				printf("Single quotes are not closed, the string is not valid\n");
				free_list_prepars(&list);
				free(line);
				exit(1);
			}
		}
		else if (prepars_list->str[0] == '\"')
		{
			if (error_prepars_quote(prepars_list->str, '\"'))
			{
				printf("Double quotes are not closed, the string is not valid\n");
				free_list_prepars(&list);
				free(line);
				exit(1);
			}
		}
		prepars_list = prepars_list->next;
	}
}
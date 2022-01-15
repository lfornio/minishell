/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 08:38:00 by lfornio           #+#    #+#             */
/*   Updated: 2022/01/15 15:31:28 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int error_prepars_quote(char *str, char c) //не закрытые кавычки
{
	int len;
	len = ft_strlen(str);
	if (len == 1 || str[len - 1] != c)
		return (1);
	return (0);
}

int print_error_for_quotes(void) // печатает ошибку если кавычки не закрыты
{
	write(2, "minishell: ", 11);
	write(2, "syntax error: unexpected end of file\n", 37);
	global_status = 258;
	return (-1);
}

int error_quote(t_prepars *prepars_list) // выход из программы при наличии незакрытых кавычек
{
	t_prepars *list;
	list = prepars_list;

	while (prepars_list)
	{
		if (prepars_list->str[0] == '\'')
		{
			if (error_prepars_quote(prepars_list->str, '\''))
				return (print_error_for_quotes());
		}
		else if (prepars_list->str[0] == '\"')
		{
			if (error_prepars_quote(prepars_list->str, '\"'))
				return (print_error_for_quotes());
		}

		prepars_list = prepars_list->next;
	}
	return (0);
}

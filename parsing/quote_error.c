/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 17:06:06 by lfornio           #+#    #+#             */
/*   Updated: 2022/02/23 12:45:51 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error_prepars_quote(char *str, char c)
{
	int	len;

	len = ft_strlen(str);
	if (len == 1 || str[len - 1] != c)
		return (1);
	return (0);
}

int	print_error_for_quotes(void)
{
	write(2, "minishell: ", 11);
	write(2, "syntax error: unexpected end of file\n", 37);
	g_status = 258;
	return (-1);
}

int	error_quote(t_prepars *prepars_list)
{
	t_prepars	*list;

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

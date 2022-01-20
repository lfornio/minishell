/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 14:48:43 by lfornio           #+#    #+#             */
/*   Updated: 2022/01/20 14:59:02 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
удаляем пробелы в начала и конце строки
*/
char	*delete_space(char *str)
{
	char	*s;
	int		len;

	s = NULL;
	len = ft_strlen(str);
	if (str[0] == ' ')
		s = ft_substr(str, 1, len - 1);
	else if (str[0] == ' ' && str[len - 1] == ' ')
		s = ft_substr(str, 1, len - 2);
	else if (str[len - 1] == ' ')
		s = ft_substr(str, 0, len - 1);
	else
		return (str);
	free(str);
	return (s);
}

/*
ищем узлы-строки без пайпов
*/
int	removing_spaces_at_the_beginning_and_end_in_str(t_prepars *list)
{
	t_prepars	*p;

	p = list;
	while (p)
	{
		if (p->str[0] != '|')
		{
			p->str = delete_space(p->str);
			if (!ft_strlen(p->str) && size_list_prepars(list) == 1)
			{
				global_status = 0;
				return (-1);
			}
		}
		p = p->next;
	}
	return (0);
}

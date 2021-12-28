/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 14:02:45 by lfornio           #+#    #+#             */
/*   Updated: 2021/12/28 13:11:48 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_command_from_str(char *str)
{
	char *s;
	int i;
	i = 0;
	while(str[i])
	{
		if(str[i] == ' ')
			break;
		i++;
	}
	s = ft_substr(str, 0, i);
	printf("s = %s\n", s);
	return(s);
}

void skip_the_quotes(char *str, int *i, char c)  //пропускаем кавычки
{
	(*i)++;
	while(str[*i])
	{
		if(str[*i] == c)
			return ;
		(*i)++;
	}
}


int get_redirect_flag(char *str)
{
	int i;
	i = 0;
	while(str[i])
	{
		if(str[i] == '\"')
			skip_the_quotes(str, &i, '\"');
		else if(str[i] == '\'')
			skip_the_quotes(str, &i, '\'');
		else if(str[i] == '>' || str[i] == '<')
			return(1);
		i++;
	}
	return (0);
}


t_cmd *push_node_cmd_firs(t_data *data, t_prepars *list) //функция создает 1ый узел в списке команд
{
	t_cmd *new;
	new = malloc(sizeof(t_cmd));
	if (!new)
	{
		printf("Error malloc\n");
		exit(1);
	}
	// new->num_cmd = data->count_commands;
	new->full_str = ft_strdup(list->str);


	new->cmd = get_command_from_str(list->str);
	new->redirect_flag = get_redirect_flag(list->str);
	printf("flag = %d\n", new->redirect_flag);
	if(!new->redirect_flag)
		{
			new->full_str_without_dollar = change_dollar_in_str(list->str, data);
			printf("full_without_$ = %s\n", new->full_str_without_dollar);






			// new->tab_cmd = ft_split(list->str, ' ');
			// for(int l = 0; new->tab_cmd[l]; l++)
			// 	printf(" %s / ", new->tab_cmd[l]);
			// printf("\n");
			// new->tab_redirect = NULL;
		}
	else
	{

	}




	return(new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 19:30:25 by lfornio           #+#    #+#             */
/*   Updated: 2022/02/02 16:39:18 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
считаем сколько пайпов
*/
int	count_pipes(t_prepars *list)
{
	t_prepars	*p;
	int			count;

	p = list;
	count = 0;
	while (p)
	{
		if (p->str[0] == '|')
			count++;
		p = p->next;
	}
	return (count);
}

/*
посчитали сколько пайпов
удалили пайпы
количество команд
envp сохранили в список
список envp сохранили в массив строк
*/
int	create_cmd(t_data *data)
{
	t_prepars	*ptr;
	int			flag;

	ptr = data->prepars;
	flag = 0;
	while (ptr)
	{
		if (flag == 0)
		{
			if (push_node_cmd_firs(&data->commands, ptr, data) < 0)
				return (-1);
		}
		else
		{
			if (push_last_node_cmd(&data->commands, ptr, data, flag) < 0)
				return (-1);
		}
		flag++;
		ptr = ptr->next;
	}
	return (0);
}

int	complete_data(t_data *data, char **envp)
{
	data->count_pipe = count_pipes(data->prepars);
	delete_node_with_pipe(data->prepars);
	data->count_commands = data->count_pipe + 1;
	data->envp_list = get_envp_list(envp);
	data->arr_envp = envp_list_remake_arr(data->envp_list);
	if (create_cmd(data) < 0)
		return (-1);
	return (0);
}

void	free_arr_envp(t_data *p)
{
	int	i;

	i = 0;
	while (p->arr_envp[i])
	{
		free(p->arr_envp[i]);
		i++;
	}
}

void	free_struct_data(t_data *list)
{
	t_data	*p;

	p = list;
	if (!list)
		return ;
	if (p->arr_envp)
	{
		free_arr_envp(p);
		free(p->arr_envp);
		p->arr_envp = NULL;
	}
	if (p->envp_list)
		free_list(&p->envp_list);
	if (p->prepars)
		free_list_prepars(&p->prepars);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshad <mshad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 19:30:25 by lfornio           #+#    #+#             */
/*   Updated: 2022/02/25 22:19:14 by mshad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	create_cmd(t_data *data, t_envp *env)
{
	t_prepars	*ptr;
	int			flag;

	ptr = data->prepars;
	flag = 0;
	while (ptr)
	{
		if (flag == 0)
		{
			if (push_node_cmd_firs(&data->commands, ptr, env) < 0)
				return (-1);
		}
		else
		{
			if (push_last_node_cmd(&data->commands, ptr, flag, env) < 0)
				return (-1);
		}
		flag++;
		ptr = ptr->next;
	}
	return (0);
}

int	complete_data(t_data *data, t_envp *env)
{
	data->count_pipe = count_pipes(data->prepars);
	delete_node_with_pipe(data->prepars);
	data->count_commands = data->count_pipe + 1;
	if (create_cmd(data, env) < 0)
		return (-1);
	if (data->count_commands == 1 && !(int)ft_strlen(data->commands->command))
		return (-1);
	return (0);
}

void	free_struct_data(t_data *list)
{
	t_data	*p;

	p = list;
	if (!list)
		return ;
	if (p->prepars)
		free_list_prepars(&p->prepars);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 17:04:11 by lfornio           #+#    #+#             */
/*   Updated: 2022/01/15 17:30:01 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_list_commands(t_cmd *list) //печатает список препарса
{
	t_cmd *p;
	p = list;
	while (p != NULL)
	{
		printf("\033[1;34m========COMMANDS========\033[0m\n");
		printf("num_cmd = \033[1;32m%d\033[0m\n", p->num_cmd);
		printf("command = \033[33m%s\033[0m\n", p->command);
		printf("argument = \033[33m%s\033[0m\n", p->argument);
		printf("tab_cmd = %p\n", p->tab_cmd);
		if (p->tab_cmd)
		{
			for (int l = 0; p->tab_cmd[l]; l++)
				printf("\033[33m%s\033[0m\n", p->tab_cmd[l]);
		}
		printf("flag_redirect = %d\n", p->redirect_flag);
		printf("name_file_heredoc = \033[31m%s\033[0m\n", p->name_file_heredoc);

		printf("redirect_ptr = %p\n", p->redirect);
		if (p->redirect)
		{
			t_redirect *q;
			q = p->redirect;
			while (q)
			{
				printf("\033[36mid = %d, fd = %d, name = %s\033[0m\n", q->id, q->fd, q->name);
				q = q->next;
			}
		}
		printf("fd_heredoc = %d\n", p->fd_heredoc);
		printf("\033[36mfd_in = %d\033[0m\n", p->fd_in);
		printf("\033[36mfd_out = %d\033[0m\n", p->fd_out);
		printf("full_str = %s\n", p->full_str);
		p = p->next;
	}
}

void print_data(t_data *data)
{
	printf("\033[1;32m=====STRUCT_DATA=======\033[0m\n");

	printf("count_commands = %d\n", data->count_commands);
	printf("count_pipe = %d\n", data->count_pipe);
	printf("t_list_envp = %p\n", data->envp_list);
	printf("t_arr_envp = %p\n", data->arr_envp);
	printf("prepars = %p\n", data->prepars);
	printf("t_cmd = %p\n", data->commands);
	if (data->commands)
		print_list_commands(data->commands);
	printf("\033[1;32m=====STRUCT_END=======\033[0m\n");
}

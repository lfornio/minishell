/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 08:09:38 by lfornio           #+#    #+#             */
/*   Updated: 2022/01/18 16:24:24 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int processing(t_data *data)
{
	// print_data(data);
	printf("parent pid = %d\n", getpid());
	int arr[data->count_commands];
	int pid;
	int flag_for_fork;
	flag_for_fork = -1;
	int number;
	number = 0;
	int **fd;

	fd = malloc(sizeof(int*) * data->count_pipe);
	if(!fd)
		return(-1);
	int k;
	k = 0;
	while(k < data->count_pipe)
	{
		fd[k] = malloc(sizeof(int) * 2);
		if(!fd[k])
			return(-1);
		k++;
	}

	// int fd[data->count_pipe][2];
	int i;
	i = 0;
	while (i < data->count_pipe)
	{
		if (pipe(fd[i]) < 0)
		{
			printf("Error pipe\n");
			return (-1);
		}
		i++;
	}
	i = 0;

	while (i < data->count_commands)
	{
		// cmd = take_node_commands_by_index(data, i);
		flag_for_fork++;
		pid = fork();
		if (pid < 0)
		{
			printf("Error fork()\n");
			return (-1);
		}
		if (pid)
		{
			arr[i] = pid;
			number++;
		}
		else if (!pid)
			break;
		i++;
	}
	if(!pid)
	{
		if(command_execution(data, flag_for_fork, fd) < 0)
			return (-1);
	}
	// if(pid)
	// {
	// 	for (int j = 0; j < data->count_commands; j++)
	// 		printf("%d ", arr[j]);
	// 	printf("\n");
	// }
	// if(!pid)
	// {
	// 	printf("child_pid = %d\n", getpid());
	// 	printf("flag_fork = %d\n", flag_for_fork);
	// 	// print_list_commands(cmd);
	// 	exit(1);
	// }

	// if (pid)
	// {
	// 	for (int j = 0; j < data->count_commands; j++)
	// 		printf("%d ", arr[j]);
	// 	printf("\n");
	// 	for (int j = 0; j < data->count_pipe; j++)
	// 	{
	// 		for (int i = 0; i < 2; i++)
	// 			printf("%d ", fd[j][i]);
	// 		printf("\n");
	// 	}

	// if (!pid)
	// {
	// 	// child
	// 	i = 0;
	// 	int k = 0;
	// 	while (k <= count)
	// 	{
	// 		if (k == number)
	// 		{
	// 			close(fd[k][1]);
	// 			close(fd[k + 1][0]);
	// 			k += 2;
	// 			continue;
	// 		}
	// 		close(fd[k][1]);
	// 		close(fd[k][0]);
	// 		k++;
	// 	}
	// 	int x;
	// 	if (read(fd[number][0], &x, sizeof(int)) < 0)
	// 	{
	// 		printf("Error read\n");
	// 		return (1);
	// 	}
	// 	x += 10;
	// 	if (write(fd[number + 1][1], &x, sizeof(int)) < 0)
	// 	{
	// 		printf("Error write\n");
	// 		return (1);
	// 	}
	// 	close(fd[number][0]);
	// 	close(fd[number + 1][1]);

	// }

	i = 0;
	while (i < data->count_commands)
	{
		waitpid(arr[i], NULL, 0);
		i++;
	}
	return(0);

}

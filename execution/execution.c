/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:24:32 by lfornio           #+#    #+#             */
/*   Updated: 2022/01/19 10:29:45 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int execution(t_data *data, char *line)
{
	// if (processing < 0) //для запуска команд
	// {
	// 	free_all(data);
	// 	free(line);
	// 	return (-1);
	// }
	global_status = 0;
	free_all(data);
	free(line);
	return(0);
}
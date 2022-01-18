/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 11:51:09 by lfornio           #+#    #+#             */
/*   Updated: 2022/01/18 12:16:52 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtins_command(char *str)
{

	if (!ft_strncmp(str, "minishell", (int)ft_strlen(str))
		|| !ft_strncmp(str, "echo", (int)ft_strlen(str))
		|| !ft_strncmp(str, "cd", (int)ft_strlen(str))
		|| !ft_strncmp(str, "pwd", (int)ft_strlen(str))
		|| !ft_strncmp(str, "export", (int)ft_strlen(str))
		|| !ft_strncmp(str, "unset", (int)ft_strlen(str))
		|| !ft_strncmp(str, "env", (int)ft_strlen(str))
		|| !ft_strncmp(str, "exit", (int)ft_strlen(str)))
			return(1);
	return(0);
}

// int builtins_command_execut(t_data *data, t_cmd *list)
// {


// 	if (!ft_strncmp(str, "minishell", (int)ft_strlen(str)))
// 		printf("MINISHELL\n");
// 	else if (!ft_strncmp(str, "echo", (int)ft_strlen(str)))
// 		printf("ECHO\n");
// 	else if (!ft_strncmp(str, "cd", (int)ft_strlen(str)))
// 		printf("CD\n");
// 	else if (!ft_strncmp(str, "pwd", (int)ft_strlen(str)))
// 		printf("pwd\n");
// 	else if (!ft_strncmp(str, "export", (int)ft_strlen(str)))
// 		printf("EXPORT\n");
// 	else if (!ft_strncmp(str, "unset", (int)ft_strlen(str)))
// 		printf("UNSET\n");
// 	else if (!ft_strncmp(str, "env", (int)ft_strlen(str)))
// 		printf("ENV\n");
// 	else if (!ft_strncmp(str, "exit", (int)ft_strlen(str)))
// 		printf("EXIT\n");
// 	else
// 		return(0);
// 	return(1);
// }

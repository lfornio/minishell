/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_funct2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshad <mshad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 12:41:37 by mshad             #+#    #+#             */
/*   Updated: 2022/02/26 12:41:38 by mshad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	command_not_found(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	g_status = 127;
	exit(g_status);
}

void	no_such_directory(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	g_status = 127;
	exit(g_status);
}

void	print_fork_error(void)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("fork failed\n", 2);
	g_status = 1;
	exit(g_status);
}

void	cd_home_error(void)
{
	ft_putstr_fd("cd: HOME not set\n", 2);
	g_status = 1;
}

void	malloc_error(void *ptr)
{
	if (ptr == NULL)
	{
		ft_putstr_fd("Error with malloc\n", 2);
		exit(EXIT_FAILURE);
	}
}

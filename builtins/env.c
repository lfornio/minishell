/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshad <mshad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 19:43:56 by mshad             #+#    #+#             */
/*   Updated: 2022/02/23 13:31:45 by mshad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(int out, char **arr_envp)
{
	int	i;

	g_status = 0;
	i = 0;
	if (arr_envp[i] == NULL)
	{
		no_file("env");
		return ;
	}
	while (arr_envp[i] != NULL)
	{
		ft_putstr_fd(arr_envp[i], out);
		ft_putchar_fd('\n', out);
		i++;
	}
}

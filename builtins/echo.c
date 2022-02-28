/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshad <mshad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 13:54:03 by mshad             #+#    #+#             */
/*   Updated: 2022/02/26 12:40:05 by mshad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_echo_nnn(char **tab_cmd)
{
	int	i;

	i = 2;
	while (tab_cmd [1][i] == 'n')
				i++;
	if (tab_cmd [1][i] == '\0')
		return (0);
	else
		return (1);
}

static int	init_flag_echo(char **tab_cmd, int out, int flag)
{
	int	i;

	i = 1;
	if (tab_cmd[1][0] == '-' && tab_cmd[1][1] == 'n'
			&& tab_cmd[1][2] == 'n')
	{
		flag = ft_echo_nnn(tab_cmd);
		if (flag == 0)
			i++;
	}
	if (!ft_strncmp(tab_cmd[1], "-n", (int)ft_strlen(tab_cmd[1])))
	{
		flag = 0;
		i++;
	}
	if (tab_cmd[i] == NULL)
		return (0);
	while (tab_cmd[i] != NULL)
	{
		ft_putstr_fd(tab_cmd[i], out);
		if (tab_cmd[i + 1])
			write(out, " ", 1);
		i++;
	}
	return (flag);
}

void	ft_echo(char **tab_cmd, int out)
{
	int	flag;

	g_status = 0;
	flag = 1;
	if (tab_cmd[1])
		flag = init_flag_echo(tab_cmd, out, flag);
	if (flag)
		write(out, "\n", 1);
}

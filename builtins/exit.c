/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshad <mshad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:15:00 by mshad             #+#    #+#             */
/*   Updated: 2022/02/23 13:30:50 by mshad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_many_arg_error(void)
{
	ft_putstr_fd("exit: too many arguments\n", 2);
	g_status = 1;
}

void	exit_not_num_error(char *val)
{
	printf("exit\n");
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(val, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	g_status = 255;
	exit(255);
}

int	sign_atoi(char *str, int *i)
{
	int	sign;

	sign = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

int	ft_atoi_mod(char *str)
{
	int			i;
	int			sign;
	uint64_t	num;
	long long	res;

	if (ft_strlen(str) > 20)
		exit_not_num_error(str);
	i = 0;
	sign = sign_atoi(str, &i);
	num = 0;
	if (!(str[i] >= '0' && str[i] <= '9'))
		exit_not_num_error(str);
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		num = num * 10 + str[i++] - '0';
	if (num > 9223372036854775807 && sign == 1)
		exit_not_num_error(str);
	if (num > 9223372036854775808U && sign == -1)
		exit_not_num_error(str);
	if (str[i] != '\0')
		exit_not_num_error(str);
	res = num * sign;
	return (res);
}

void	ft_exit(t_data *data, char **tab_cmd)
{
	long long	num_exit;
	int			mod_num;
	int			size;

	if (data->count_commands)
		size = data->count_commands;
	if (!tab_cmd[1])
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	num_exit = ft_atoi_mod(tab_cmd[1]);
	if (tab_cmd[2] != NULL)
	{
		exit_many_arg_error();
		return ;
	}
	mod_num = num_exit % 256;
	g_status = mod_num;
	if (size == 1)
		printf("exit\n");
	exit(mod_num);
}

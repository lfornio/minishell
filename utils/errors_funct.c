/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_funct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshad <mshad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 12:41:47 by mshad             #+#    #+#             */
/*   Updated: 2022/02/26 12:41:48 by mshad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	g_status = errno;
	exit(errno);
}

void	no_file(char *filename)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	g_status = 1;
}

void	unset_args_error(char *val)
{
	ft_putstr_fd("unset: `", 2);
	ft_putstr_fd(val, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_status = 1;
}

void	ft_2d_array_free(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		s[i] = NULL;
		i++;
	}
	free(s);
	s = NULL;
}

int	ft_isdigit_yes(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

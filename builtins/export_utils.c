/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_export_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshad <mshad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 13:11:34 by mshad             #+#    #+#             */
/*   Updated: 2022/02/23 13:41:08 by mshad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	key_chars(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	return (0);
}

static int	ft_key_error_arg(char *cmnd, char *arg)
{
	ft_putstr_fd("msh: `", 2);
	ft_putstr_fd(cmnd, 2);
	write(2, ": `", 3);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_status = 1;
	return (1);
}

int	key_validation(char *cmd, char *arg)
{
	int	i;

	if (arg[0] == '=' || ft_isdigit(arg[0]) || !key_chars(arg[0]))
		return (ft_key_error_arg(cmd, arg));
	i = 0;
	if (ft_strcmp(cmd, "export") == 0)
	{
		while (arg[i] && arg[i] != '=')
		{
			if (!key_chars(arg[i]) && !ft_isdigit(arg[i]))
				return (ft_key_error_arg(cmd, arg));
		i++;
		}
	}
	else
	{
		while (arg[i])
		{
			if ((!key_chars(arg[i]) && !ft_isdigit(arg[i])) || arg[i] == '=')
				return (ft_key_error_arg(cmd, arg));
			i++;
		}
	}
	return (0);
}

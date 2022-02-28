/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshad <mshad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:41:20 by mshad             #+#    #+#             */
/*   Updated: 2022/02/23 13:37:36 by mshad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_pwd(void)
{
	char	*str;
	char	*cur_dir;

	str = malloc(sizeof(char) * 512);
	malloc_error(str);
	cur_dir = getcwd(str, 512);
	if (!cur_dir)
		ft_putstr_fd(strerror(errno), 2);
	return (cur_dir);
}

void	ft_pwd(int out)
{
	char	*cur_dir;

	g_status = 0;
	cur_dir = get_pwd();
	ft_putstr_fd(cur_dir, out);
	free(cur_dir);
	ft_putchar_fd('\n', out);
}

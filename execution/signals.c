/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshad <mshad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 10:34:22 by mshad             #+#    #+#             */
/*   Updated: 2022/02/26 18:32:56 by mshad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cntrl_c2(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	errno = 1;
	g_status = errno;
	return ;
}

void	cntrl_c(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
	write(2, "  \b\b\n", 5);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	errno = 1;
	g_status = errno;
	return ;
}

void	signals(void)
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGINT, cntrl_c);
	signal(SIGQUIT, SIG_IGN);
	return ;
}

void	input_eof(void)
{
	write(STDOUT_FILENO, "exit\n", 5);
	exit(EXIT_SUCCESS);
}

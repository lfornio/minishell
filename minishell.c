/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:38:49 by lfornio           #+#    #+#             */
/*   Updated: 2021/12/14 15:52:07 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv)
{
	if(argc != 1)
	{
		printf("Error arguments\n");
		exit(1);
	}
	printf("%s\n", argv[0]);
	char *start;
	while(1)
	{
		start = readline("\001\033[32m\002minishell> \001\033[0m\002");
		add_history(start);
		printf("s = %s\n", start);
		free(start);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:58:41 by lfornio           #+#    #+#             */
/*   Updated: 2022/01/07 15:21:51 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char *processing_a_redirect_heredoc(char *str, t_data *data, int *flag, int i)
// {

// }

// char *processing_a_redirect_in(char *str, t_data *data, int *flag, int i)
// {

// }

// char *redirect_input(char *line, t_data *data, int *flag)
// {
// 	char *tmp;
// 	char *before;
// 	char *after;
// 	char *s;

// 	tmp = ft_strchr(line, '<');
// 	before = ft_substr(line, 0, ft_strlen(line) - ft_strlen(tmp));
// 	if (ft_strnstr(tmp, "<<", 2))
// 		after = processing_a_redirect_heredoc(tmp, data, flag, REDIRECT_INPUT_TWO);
// 	else
// 		after = processing_a_redirect_in(tmp, data, flag, REDIRECT_INPUT_ONE);
// 	s = ft_strjoin(before, after);
// 	free(line);
// 	char *p;
// 	free(before);
// 	free(after);
// 	p = remove_extra_spaces_and_tabs_in_str(s);
// 	p = delete_space(p);
// 	return (p);


// }

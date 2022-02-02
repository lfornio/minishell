/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_name_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:21:41 by lfornio           #+#    #+#             */
/*   Updated: 2022/02/02 17:12:21 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_name_file(char *str, int *i)
{
	while (str[*i] && str[*i] != ' ' && str[*i] != '|'
		&& str[*i] != '>' && str[*i] != '<')
	{
		if (str[*i] == '\'')
			skip_the_quotes(str, i, '\'');
		if (str[*i] == '\"')
			skip_the_quotes(str, i, '\"');
		(*i)++;
	}
}

char	*get_name_file(char *str, int *i, int a, t_data *data)
{
	char	*name_file;
	char	*tmp;

	if (str[a] == ' ')
		tmp = ft_substr(str, a + 1, *i - a - 1);
	else
		tmp = ft_substr(str, a, *i - a);
	name_file = change_dollar_in_str(tmp, data);
	if (!ft_strlen(name_file))
	{
		write(2, "minishell: ", 11);
		write(2, tmp, ft_strlen(tmp));
		write(2, ": ", 2);
		write(2, "ambiguous redirect\n", 19);
		free(tmp);
		free(name_file);
		return (NULL);
	}
	free(tmp);
	return (name_file);
}

int	founding_name_file(char *str, int *i)
{
	if (str[*i] == ' ')
		(*i)++;
	if ((str[*i] == '>' && (print_error_token(">") < 0))
		|| (str[*i] == '<' && (print_error_token("<") < 0)))
		return (-1);
	else
		skip_name_file(str, i);
	return (0);
}

char	*name_file(char *str, int *i, int a, t_data *data)
{
	char	*name;

	if (founding_name_file(str, i) < 0)
		return (NULL);
	name = get_name_file(str, i, a, data);
	return (name);
}

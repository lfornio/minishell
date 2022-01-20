/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:44:58 by lfornio           #+#    #+#             */
/*   Updated: 2022/01/20 20:20:28 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void push_last_node_redirect(t_redirect **list, char *str, int fd, int a) //функция добавляет узел в конец списка
{
	t_redirect *tmp;
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;

	t_redirect *new;
	new = malloc(sizeof(t_redirect));
	printf("redirect_out_24 = %p\n", new);
	if (!new)
	{
		printf("Error malloc\n");
		return ;
	}
	new->name = ft_strdup(str);
	new->fd = fd;
	new->id = a;
	new->next = NULL;
	tmp->next = new;
}

int print_error_token(char *s)
{
		write(2, "minishell: syntax error near unexpected token `", 47);
		write(2, s, ft_strlen(s));
		write(2, "'\n", 2);
		global_status = 258;
		return (-1);
}

void push_node_redirect(t_redirect **list, char *str, int fd, int a) //функция создает 1ый узел
{
	t_redirect *new;
	new = malloc(sizeof(t_redirect));
	if (!new)
	{
		return;
	}
	new->name = ft_strdup(str);
	new->fd = fd;
	new->id = a;
	new->next = *list;
	*list = new;
	}

	int open_name_file_for_write(char *name) // открываем файл для записи
{
	int fd;

	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		write(2, "minishell: ", 11);
		perror(name);
		free(name);
		// global_status = 1;
		return (-1);
	}
	return (fd);
}


char *processing_a_redirect_out(t_cmd *node, char *str, t_data *data, int *flag, int i) // >
{
	int		a;
	int		fd;
	char	*name;
	char	*after;

	a = i;
	name = name_file(str, &i, a, data);

	if (!name || (fd = open_name_file_for_write(name)) < 0)
	{
		free(str);
		global_status = 1;
		return (NULL);
	}
	if ((*flag) == 0)
		push_node_redirect(&node->redirect, name, fd, a);
	else
		push_last_node_redirect(&node->redirect, name, fd, a);
	(*flag)++;
	free (name);
	after = ft_substr(str, i, ft_strlen(str) - i);
	free(str);
	return (after);
}

char *redirect_output(t_cmd *node, char *line, t_data *data, int *flag)
{
	char *tmp;
	char *before;
	char *after;
	char *s;
	char *p;

	p = NULL;
	tmp = ft_strdup(ft_strchr(line, '>'));
	before = ft_substr(line, 0, ft_strlen(line) - ft_strlen(tmp));
	// free(line);
	if (ft_strnstr(tmp, ">>", 2))
		after = processing_a_redirect_out(node, tmp, data, flag, REDIRECT_OUTPUT_TWO);
	else
		after = processing_a_redirect_out(node, tmp, data, flag, REDIRECT_OUTPUT_ONE);
	// if(!ft_strlen(after))
	// {
	// 	free(after);
	// 	return(p);
	// }
	if(!after)
	{
		free(before);
		return(NULL);
	}
	s = ft_strjoin(before, after);
	free(before);
	free(after);
	p = remove_extra_spaces_and_tabs_in_str(s);
	p = delete_space(p);
	return (p);
}

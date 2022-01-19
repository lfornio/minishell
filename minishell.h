/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:45:51 by lfornio           #+#    #+#             */
/*   Updated: 2022/01/19 11:12:41 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include "libft/libft.h"

#define REDIRECT_OUTPUT_ONE 1
#define REDIRECT_OUTPUT_TWO 2
#define REDIRECT_INPUT_ONE 3
#define REDIRECT_INPUT_TWO 4

int global_status;

typedef struct s_list  //односвязный список env
{
	char *key; //ключ до =
	char *value; //значение после =
	struct s_list *next;
} t_list;

typedef struct s_prepars  //вспомогательный односвязный список для препарсинга
{
	char *str;
	struct s_prepars *next;
} t_prepars;

typedef struct s_redirect //вспомогательный односв.список для редиректов
{
	char *name;
	int fd;
	int id;
	struct s_redirect *next;
} t_redirect;

typedef struct s_cmd //односвязный список команд. Один узел содержит следующие поля:
{
	int num_cmd; //номер команды (1-ая команда == 0)
	char *command; // команда
	char *argument; // аргументы команды
	char **tab_cmd; //массив строк (1-я строка команда, остальные аргументы)
	int redirect_flag;  //флаг есть ли редиректы
	t_redirect *redirect; // если есть редиректы, создаем вспомогательный список для редиректов с fd и именами файлов
	char *name_file_heredoc; //если есть << создаем временный файл .file
	int fd_heredoc; //флаг есть ли <<
	int fd_in; //fd на чтение(откуда читаем)
	int flag_fd_in; // 3 если < или 4 если <<
	int fd_out; //fd на запись(куда записываем)
	int flag_fd_out;// 1 если > или 2 если >>
	char *full_str; // вспомогательная строка (полная) для парсинга
	struct s_cmd *next; // следующий узел
} t_cmd;

typedef struct s_data
{
	int count_commands;  //количество команд
	int count_pipe; //количество пайпов
	t_cmd *commands; // список команд
	t_list *envp_list; // список env
	char **arr_envp; // массив строк env
	t_prepars *prepars; // след.узел
} t_data;



int parsing(t_data *data, char *line, char **envp);
int preparsing(t_data *data, char *line);
char *processing_quote(char *str, int *i);
void skip_the_quotes(char *str, int *i, char c);
int error_quote(t_prepars *prepars_list);
void push_node_prepars(t_prepars **p_list, char *str);
void push_last_node_prepars(t_prepars **list, char *str);
void removing_spaces_and_tabs_in_list(t_prepars *list);
char *remove_extra_spaces_and_tabs_in_str(char *str);
int search_for_pipes(t_prepars *list);
int error_last_pipe(t_prepars *list);
t_prepars *a_new_node_in_the_middle(t_prepars *middle, char *str);
char **prepars_list_remake_arr(t_prepars *list);
void remove_quote(t_prepars **list);










int execution(t_data *data, char *line); //начинаются функции реализации команд










void pars_envp_str(t_list *list, char *str);
void push_node(t_list **list, char *str);
void push_last_node(t_list **list, char *str);
void	free_list(t_list **list);
void print_list(t_list **list);
// char *prepersing_str(char *str, int *i);

void free_list_prepars(t_prepars **list);
void print_list_prepars(t_prepars *list);

int size_list_prepars(t_prepars *list);
int size_list_envp(t_list *list);


void gluing_strings_without_pipe(t_prepars *list);
int removing_spaces_at_the_beginning_and_end_in_str(t_prepars *list);

int count_pipes(t_prepars *list);
char *get_str_from_list(t_prepars *list, int index);
void delete_node_with_pipe(t_prepars *list);
t_prepars *delete_node_prepars(t_prepars *p, t_prepars *head) ;

t_list *get_envp_list(char **envp);
void print_list(t_list **list);
char *change_dollar_in_str(char *str, t_data *data);
char **envp_list_remake_arr(t_list *list);
int push_node_cmd_firs(t_cmd **commands, t_prepars *list, t_data *data);
char *processing_the_dollar(char *str, int *i, t_data *data);
char **split_str_whitespace_for_execve(char *str, t_data *data);

char *get_argumens(char *str);
char *removing_the_quotes(char *str, int *i, char c);
char *redirect_processing(t_cmd *node, char *str, t_data *data, int *flag);
int get_redirect_flag(char *str) ;
char *delete_space(char *str);
int print_error_token(char *s);

t_prepars *get_ptr_from_list(t_prepars *list, int index);
void delete_last_node_prepars(t_prepars *p, t_prepars *head);
int found_char_c(char *str, char c);
t_prepars *delete_node_prepars(t_prepars *p, t_prepars *head);
char *get_str_from_list(t_prepars *list, int index);

int complete_data(t_data *data, char **envp);
void free_all(t_data *data);
char *redirect_output(t_cmd *node, char *line, t_data *data, int *flag);
char *redirect_input(t_cmd *node, char *line, t_data *data, int *flag);
void free_cmd(t_cmd **list);
int size_list_redirect(t_redirect *list) ;
void push_last_node_redirect(t_redirect **list, char *str, int fd, int a);
void push_node_redirect(t_redirect **list, char *str, int fd, int a);
void skip_name_file(char *str, int *i);
char *get_name_file(char *str, int *i, int a, t_data *data);
int open_name_file_for_read(char *name);
int founding_name_file(char *str, int *i);
int open_name_file_for_write(char *name);
char *processing_a_redirect_heredoc(t_cmd *node, char *str, t_data *data, int *flag, int i);
char *name_file(char *str, int *i, int a, t_data *data);
void get_fd_in_and_out_for_redirect(t_cmd *node, t_data *data);
char *get_command_from_str(char *str);
void free_redirect(t_redirect **list);
int push_last_node_cmd_firs(t_cmd **commands, t_prepars *list, t_data *data, int num);
int print_error_for_quotes(void);
void print_data(t_data *data);
void free_list_commands(t_cmd **list);
void init_cmd(t_cmd *list);
int processing(t_data *data);
void print_list_commands(t_cmd *list);
int command_execution(t_data *data, int flag_for_fork, int **fd);
int builtins_command_execut(t_data *data, t_cmd *list);
int builtins_command(char *str);

#endif

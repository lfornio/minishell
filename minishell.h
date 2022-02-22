/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:45:51 by lfornio           #+#    #+#             */
/*   Updated: 2022/02/22 15:47:05 by lfornio          ###   ########.fr       */
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
# include <readline/history.h>
# include "libft/libft.h"

#define OUTPUT_ONE 1
#define OUTPUT_TWO 2
#define INPUT_ONE 3
#define INPUT_TWO 4

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
	// t_list *envp_list; // список env
	// char **arr_envp; // массив строк env
	t_prepars *prepars; // след.узел
} t_data;

typedef struct s_envp
{
	t_list *envp_list; // список env
	t_list *envp_list_sort; // список env сортированный
	char **arr_envp; // массив строк env
} t_envp;

typedef struct s_params
{
	t_cmd *node;
	char *tmp;
}t_params;

typedef struct s_dollar
{
	char *before;
	char *after;
	char *value;
	char *tmp;
}t_dollar;

/*-----------------PARSING--------------------*/
char		**split_str_whitespace_for_execve(char *str, t_envp *env);
int			push_node_cmd_firs(t_cmd **commands, t_prepars *list, t_envp * env);
int			push_last_node_cmd(t_cmd **commands, t_prepars *list, int num, t_envp *env);
int			complete_data(t_data *data, t_envp *env);
void		free_struct_data(t_data *list);
char		*processing_the_dollar(char *str, int *i, t_envp *env);
char		*removing_the_dollar_before_quotes(char *str, int *i);
char		*removing_the_quotes(char *str, int *i, char c);
char		*removing_the_double_quotes(char *str, int *i, t_envp *env);
char		*get_change_str_without_dollar(t_dollar *dollar, char c, int *i);
char		*change_dollar_in_str(char *str, t_envp *env);
char		*after_dollar_char(char *str, int *i, t_envp *env);
t_list		*get_envp_list(char **envp);
char		**envp_list_remake_arr(t_list *list);
void		print_envp_list(t_list **list);
void		free_list(t_list **list);
void		free_all(t_data *data);
int			search_for_pipes(t_prepars *list);
void		delete_node_with_pipe(t_prepars *list);
int			error_last_pipe(t_prepars *list);
void		push_node_prepars(t_prepars **p_list, char *str);
void		push_last_node_prepars(t_prepars **list, char *str);
void		delete_last_node_prepars(t_prepars *p, t_prepars *head);
t_prepars	*a_new_node_in_the_middle(t_prepars *middle, char *str);
t_prepars	*delete_node_prepars(t_prepars *p, t_prepars *head);
void		free_list_prepars(t_prepars **list);
void		print_list_prepars(t_prepars *list);
char		*get_str_from_list(t_prepars *list, int index);
int			size_list_prepars(t_prepars *list);
char		**prepars_list_remake_arr(t_prepars *list);
int			preparsing(t_data *data, char *line);
int			print_error_for_quotes(void);
int			error_quote(t_prepars *prepars_list);
void		skip_the_quotes(char *str, int *i, char c);
char		*processing_quote(char *str, int *i);
void		remove_quote(t_prepars **list);
int			get_redirect_flag(char *str);
int			no_redirect_flag(t_cmd *node, char *str, t_envp *env);
int			yes_redirect_flag(t_cmd *node, char *str, int *flag, t_envp *env);
void		get_fd_in_and_out_for_redirect(t_cmd *node);
char		*process_heredoc(t_params param, t_envp *env, int *flag, int i);
int			open_name_file_for_read(char *name);
char		*redirect_input(t_cmd *node, char *line, t_envp *env, int *flag);
int			size_list_redirect(t_redirect *list);
void		free_redirect(t_redirect **list);
void		push_node_redirect(t_redirect **list, char *str, int fd, int a);
void		push_last_node_redirect(t_redirect **list, char *str, int fd, int a);
void		free_list_redirect(t_redirect **list);
char		*name_file(char *str, int *i, int a, t_envp *env);
int			open_name_file_for_write(char *name);
char		*redirect_output(t_cmd *node, char *line, t_envp *env, int *flag);
char		*redirect_processing(t_cmd *node, char *str, int *flag, t_envp *env);
int			print_error_token(char *s);
void		close_extra_fd(t_cmd *node, t_redirect *list);
char		*remove_extra_spaces_and_tabs_in_str(char *str);
char		*delete_space(char *str);
int			removing_spaces_at_the_beginning_and_end_in_str(t_prepars *list);
void		remove_space(char *tmp, char *str);
void		init_env(t_envp *env_struct, char **envp);
void		free_env_struct(t_envp *env);
t_prepars	*get_ptr_from_list(t_prepars *list, int index);
int			error_last_node(t_prepars *list);

/*-----------------EXECUTION--------------------*/
int execution(t_data *data, char *line); //начинаются функции реализации команд
int command_execution(t_data *data, int flag_for_fork, int **fd);
int processing(t_data *data);
int builtins_command_execut(t_data *data, t_cmd *list);
int builtins_command(char *str);
void print_data(t_data *data);


#endif

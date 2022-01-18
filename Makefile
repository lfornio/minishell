NAME		= 	minishell
SRCS		= 	minishell.c \
				func_1.c \
				func_2.c \
				func_3.c \
				func_4.c \
				func_5.c \
				func_6.c \
				func_7.c \
				func_8.c \
				func_9.c \
				func_10.c \
				func_11.c \
				prepars_list.c \
				redirect_output.c \
				redirect_input.c \
				redirect_input_heredoc.c \
				redirect_get_fd_in_and_out.c \
				print_data.c \
				redirect_processing.c \
				free_all_struct_data.c \
				processing.c \
				command_execution.c \
				builtins.c



CC 			= 	gcc
FLAGS		=	 -g -Wall -Wextra -Werror
INCLUDES	=	minishell.h
INC_READLINE	=	-I/Users/$(USER)/.brew/Cellar/readline/8.1.1/include
LIB_READLINE	=	-L/Users/$(USER)/.brew/Cellar/readline/8.1.1/lib
LIBFT_A		=   libft/libft.a
OBJS		=	$(SRCS:.c=.o)

.c.o: $(INCLUDE)
	$(CC) $(FLAGS) -c $< -o $@

${NAME}: $(OBJS) $(INCLUDE)
	$(MAKE) -C ./libft
	$(CC) $(FLAGS) $(OBJS) $(LIBFT_A) -lreadline $(INC_READLINE)  $(LIB_READLINE) -o $(NAME)

all : libft $(NAME)

clean :
	make -C libft clean
	rm -f $(OBJS)


fclean : clean
	rm -f libft/libft.a
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re

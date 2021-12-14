NAME		= 	minishell
SRCS		= 	minishell.c

CC 			= 	gcc
FLAGS		=	-Wall -Wextra -Werror
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
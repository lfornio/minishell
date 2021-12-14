# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfornio <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/04 07:47:43 by lfornio           #+#    #+#              #
#    Updated: 2021/05/11 22:53:29 by lfornio          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a
HEAD	=	libft.h
SRCS	=	ft_atoi.c ft_strlen.c ft_toupper.c ft_tolower.c ft_strncmp.c ft_putchar_fd.c \
			ft_putstr_fd.c ft_isalpha.c ft_isascii.c ft_isprint.c ft_isdigit.c \
			ft_isalnum.c ft_strchr.c ft_strrchr.c ft_strdup.c ft_calloc.c ft_putnbr_fd.c \
			ft_putendl_fd.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memchr.c \
			ft_memmove.c ft_memcmp.c ft_strlcpy.c ft_strlcat.c ft_strnstr.c ft_substr.c \
			ft_strjoin.c ft_strtrim.c ft_strmapi.c ft_itoa.c ft_split.c
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra
AR		=	ar rcs
RM		=	rm -f

OBGS	=	 ${SRCS:.c=.o}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBGS} 
	${AR} ${NAME} ${OBGS} ${HEAD}
	
all: 	${NAME}

clean:
	${RM} ${OBGS}

fclean: clean
	${RM} ${NAME}

re:  	fclean all

.PHONY: all clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/29 15:58:43 by dcyprien          #+#    #+#              #
#    Updated: 2022/04/28 19:47:21 by dcyprien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	./main.c\
			./srcs/malloc_utils.c\
			./srcs/parsing.c\
			./srcs/ft_substr.c\
			./srcs/ft_strlen.c\
			./srcs/ft_strdup.c\
			./srcs/ft_split.c\
			./srcs/ft_memmove.c\
			./srcs/ft_memcpy.c\
			./srcs/ft_strncmp.c\
			./srcs/ft_strcat.c\
			./srcs/ft_calloc.c\
			./srcs/ft_bzero.c\
			./srcs/ft_strchr.c\
			./srcs/ft_strjoin.c\
			./srcs/builtins.c\
			./srcs/env_mgt.c\
			./srcs/builtins1.c\
			./srcs/cmd_utils.c\
			./srcs/parsing_utils.c\
			./srcs/ft_isascii.c\
			./srcs/ft_cinset.c\
			./srcs/redirections.c\
			./srcs/ft_isalnum.c\
			./srcs/ft_isdigit.c\
			./srcs/ft_isalpha.c\
			./srcs/parsing_utils_2.c\
			./srcs/expansions.c\
			./srcs/malloc_utils_2.c\
			./srcs/signal.c\
			./srcs/ft_memset.c\
			./srcs/pipes.c\
			./srcs/error_mgt.c\
			./srcs/env_mgt_2.c\
			./srcs/cmd_utils_2.c\
			./srcs/error_mgt_2.c\
			./srcs/execution.c\
			./srcs/builtins_utils.c\
			./srcs/split_utils.c

OBJS	=	${SRCS:.c=.o}

CC		=	cc

CFLAGS	=	-Wall -Werror -Wextra -g3

NAME	=	minishell

.c		:	.o
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}	:	${OBJS}
		${CC} ${CFLAGS} ${OBJS} -lreadline -o ${NAME}

all		:	${NAME}

clean	:
			rm -rf ${OBJS}

fclean	:	clean
			rm -rf ${NAME}
			$(MAKE) -C . clean

re	:	fclean all

.PHONY	:	all clean fclean re

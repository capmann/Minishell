# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/29 15:58:43 by dcyprien          #+#    #+#              #
#    Updated: 2022/05/07 01:19:11 by dcyprien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	./srcs/main.c\
			./srcs/parsing/malloc_utils.c\
			./srcs/parsing/parsing.c\
			./srcs/libft/ft_substr.c\
			./srcs/libft/ft_strlen.c\
			./srcs/libft/ft_strdup.c\
			./srcs/libft/ft_split.c\
			./srcs/libft/ft_memmove.c\
			./srcs/libft/ft_memcpy.c\
			./srcs/libft/ft_strncmp.c\
			./srcs/libft/ft_strcat.c\
			./srcs/libft/ft_calloc.c\
			./srcs/libft/ft_bzero.c\
			./srcs/libft/ft_strchr.c\
			./srcs/libft/ft_strjoin.c\
			./srcs/env/builtins.c\
			./srcs/env/env_mgt.c\
			./srcs/env/builtins1.c\
			./srcs/parsing/cmd_utils.c\
			./srcs/parsing/parsing_utils.c\
			./srcs/libft/ft_isascii.c\
			./srcs/libft/ft_cinset.c\
			./srcs/execution/redirections.c\
			./srcs/libft/ft_isalnum.c\
			./srcs/libft/ft_isdigit.c\
			./srcs/libft/ft_isalpha.c\
			./srcs/parsing/parsing_utils_2.c\
			./srcs/env/expansions.c\
			./srcs/parsing/malloc_utils_2.c\
			./srcs/execution/signal.c\
			./srcs/libft/ft_memset.c\
			./srcs/execution/pipes.c\
			./srcs/parsing/error_mgt.c\
			./srcs/env/env_mgt_2.c\
			./srcs/parsing/cmd_utils_2.c\
			./srcs/parsing/error_mgt_2.c\
			./srcs/execution/execution.c\
			./srcs/env/builtins_utils.c\
			./srcs/libft/split_utils.c\
			./srcs/execution/signal_2.c\
			./srcs/env/builtins_utils_2.c\
			./srcs/execution/pipes_utils.c\
			./srcs/parsing/error_mgt_3.c\
			./srcs/env/builtins_utils_3.c\
			./srcs/parsing/malloc_utils_3.c

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

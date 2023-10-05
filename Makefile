# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/26 14:35:18 by codespace         #+#    #+#              #
#    Updated: 2023/10/05 11:20:22 by abied-ch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS =  src/pipex.c \
		src/children.c \
		src/arguments.c \
		utils/cleanup.c \
		utils/initialize.c \

OBJS = ${SRCS:.c=.o}

CC = cc

CFLAGS = -Wall -Wextra -Werror -Iincludes -g

RM = rm -rf

all: ${NAME} ${CHECK}
${NAME}: ${OBJS}
	@${MAKE} -C ./libft --no-print-directory
	@${CC} ${CFLAGS} ${OBJS} ./libft/libft.a -o ${NAME}

clean: 
	@${MAKE} -C ./libft --no-print-directory fclean
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME}

re: fclean all
	
.PHONY: all clean fclean re


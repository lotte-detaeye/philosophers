# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/21 16:17:36 by lde-taey          #+#    #+#              #
#    Updated: 2024/07/17 17:20:24 by lde-taey         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGS = -Werror -Wall -Wextra

SRCS = main.c init.c utils.c utils_args.c actions.c \
	routine.c cleanup.c utils_2.c monitoring.c utils_print.c\

OBJS = $(SRCS:.c=.o)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -lpthread $(OBJS) -o $(NAME)

.PHONY : all clean fclean re

all : $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/02 17:46:17 by eghalime          #+#    #+#              #
#    Updated: 2024/11/27 18:01:16 by eghalime         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	eat_1.c eat_2.c \
		getters.c\
		init.c monitor.c parse.c philo.c routine.c \
		setters.c sleep.c think.c time.c utils.c 

OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror

CC = cc
RM = rm -rf

NAME = philo


all: $(NAME)

$(NAME): $(OBJS) 
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) 

%.o: %.c philo.h
	$(CC) $(FLAGS) -c $< -o $@ 

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
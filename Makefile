# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: razamora <razamora@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/06 07:33:42 by razamora          #+#    #+#              #
#    Updated: 2024/11/10 16:29:58 by razamora         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo
CC = cc
FRM = rm -rf
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=thread
SRCS = philo.c monitoring.c thread.c utils.c parse.c eating.c
OBJS = ${SRCS:.c=.o}

OBJS	  = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) 
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	
clean:
	$(FRM) $(OBJS)

fclean: clean
	$(FRM) $(NAME)

re: fclean all

.PHONY: re fclean clean all
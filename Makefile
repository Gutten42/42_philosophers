# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vgutten <vgutten@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/06 14:55:20 by vguttenb          #+#    #+#              #
#    Updated: 2022/04/19 11:39:32 by vgutten          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra
THFLAG = -pthread

SRCS = philo.c \
		philo_utils.c \
		get_time.c \
		set_gen_var.c \
		phil_func_log_nou.c \
		log_state.c \
		no_usleep.c \
		setup_phils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) Makefile
	$(CC) $(THFLAG) $(CFLAGS) -o $(NAME) $(OBJS)

test: $(NAME)
	./$(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	
re: fclean all

.PHONY: all clean fclean re
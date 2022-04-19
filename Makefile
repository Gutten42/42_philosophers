# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/06 14:55:20 by vguttenb          #+#    #+#              #
#    Updated: 2022/04/19 20:21:12 by vguttenb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra
THFLAG = -pthread #-fsanitize=thread

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
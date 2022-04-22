# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/06 14:55:20 by vguttenb          #+#    #+#              #
#    Updated: 2022/04/22 19:30:21 by vguttenb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
BNS_NAME = philo_bonus
CC = cc
CFLAGS = -Wall -Werror -Wextra
THFLAG = -pthread #-fsanitize=thread

SRCS = philo.c \
		phil_func.c \
		setup_phils.c

CMN = get_time.c \
		philo_utils.c \
		no_usleep.c \
		set_gen_var.c

BNS = philo_bonus.c \
		phil_func_bonus.c 

OBJS = $(SRCS:.c=.o)

CMN_OBJS = $(CMN:.c=.o)

BNS_OBJS = $(BNS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(CMN_OBJS) Makefile
	$(CC) $(THFLAG) $(CFLAGS) -o $(NAME) $(OBJS) $(CMN_OBJS)

bonus: $(BNS_OBJS) $(CMN_OBJS) Makefile
	$(CC) $(CFLAGS) -o $(BNS_NAME) $(BNS_OBJS) $(CMN_OBJS)

test: $(NAME)
	./$(NAME)

clean:
	rm -f $(OBJS) $(CMN_OBJS) $(BNS_OBJS)

fclean: clean
	rm -f $(NAME) $(BNS_NAME)
	
re: fclean all

.PHONY: all clean fclean re
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:53:33 by vguttenb          #+#    #+#             */
/*   Updated: 2022/04/18 16:11:37 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

# define THINKING " is thinking"
# define EATING " is eating"
# define SLEEPING " is sleeping"
# define FORK " has taken a fork"

typedef struct s_gen
{
	struct timeval	time;
	pthread_mutex_t	print_right;
	int				nr_of_phil;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	char			end;
}				t_gen;

typedef struct s_phill
{
	pthread_t		mind;
	int				index;
	int				last_meal;
	int				nr_meals;
	pthread_mutex_t	l_fork;
	t_gen			*gen_var;
	struct s_phill	*next;
}				t_phill;

int		get_time(struct timeval *time);
t_phill	*release_the_phils(t_gen *gen_var);
void	set_gen_var(t_gen *gen_var, int argc, char **argv);
void	*leftie_phil(void *data);
void	*rightie_phil(void *data);
void	log_state(pthread_mutex_t *print_right, int timestamp, int index, char *state);
void	no_usleep(int wait, int cadency, struct timeval *time);

int		ft_isdigit(int value);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_bzero(void *memdir, size_t len);
void	ft_putchar_fd(char c, int fd);
char	*ft_itoa(int n);
size_t	ft_strlen(const char *str);

#endif
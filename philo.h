/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgutten <vgutten@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:53:33 by vguttenb          #+#    #+#             */
/*   Updated: 2022/04/19 11:57:08 by vgutten          ###   ########.fr       */
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
	int				nr_phil;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				max_meals;
	char			end;
	pthread_mutex_t	pr_mutex;
	struct timeval	time;
}				t_gen;

typedef struct s_phil
{
	int				index;
	int				last_meal;
	int				nr_meals;
	int				max_meals;
	int				t_eat;
	int				t_sleep;
	char			*end;
	struct timeval	*time;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*pr_mutex;
	pthread_t		mind;
	pthread_mutex_t	fork;
	struct s_phil	*next;
}				t_phil;

int	get_time(struct timeval *time);
t_phil	*setup_phils(t_gen *gen_var);
void	set_gen_var(t_gen *gen_var, int argc, char **argv);
void	*leftie_phil(void *data);
/* void	*rightie_phil(void *data); */
void	log_state(pthread_mutex_t *print_right, int timestamp, int index, char *state);
void	no_usleep(struct timeval *time, int wait, int cadency);

int		ft_isdigit(int value);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_bzero(void *memdir, size_t len);
void	ft_putchar_fd(char c, int fd);
char	*ft_itoa(int n);
size_t	ft_strlen(const char *str);

#endif
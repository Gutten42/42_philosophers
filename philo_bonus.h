/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:53:33 by vguttenb          #+#    #+#             */
/*   Updated: 2022/04/25 17:56:45 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>
# include <fcntl.h>
# include <semaphore.h>
# include <signal.h>


# define THINKING "is thinking"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define FORK "has taken a fork"

typedef struct s_gen
{
	int				nr_phil;
	int				t_start;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				max_meals;
	//char			end;
	// int				*last_meals;
	// int				*nr_meals;
	sem_t			*forks;
	sem_t			*bowl;
	sem_t			*sat;
	pid_t			*minds;
	struct timeval	time;
}				t_gen;

typedef struct s_phil
{
	int				index;
	int				nr_phil;
	int				*last_meal;
	int				nr_meals;
	int				max_meals;
	int				t_eat;
	int				t_sleep;
	int				t_start;
	sem_t			*forks;
	sem_t			*bowl;
	sem_t			*sat;
	struct timeval	*time;
}				t_phil;

typedef struct s_input
{
	int				index;
	int				*last_meal;
	int				*nr_meals;
	struct s_gen	*gen_var;
}				t_input;


int		get_time(struct timeval *time, int t_start);
void	set_gen_var(t_gen *gen_var, int argc, char **argv);
void	phil_bonus_sp(int ind, t_gen *gen_var);
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
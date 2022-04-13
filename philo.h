/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:53:33 by vguttenb          #+#    #+#             */
/*   Updated: 2022/04/13 20:27:19 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_gen
{
	int				nr_of_phil;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nr_of_meals;
}				t_gen;

typedef struct s_phill
{
	int				index;
	int				last_meal;
	pthread_mutex_t	r_fork;
	struct s_phill	*next;
	struct s_phill	*prev;
}				t_phill;

int		ft_isdigit(int value);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);

////////////

void	ft_putnbr_fd(int n, int fd);

#endif
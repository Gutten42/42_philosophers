/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_func_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:35:02 by vgutten           #+#    #+#             */
/*   Updated: 2022/04/22 19:39:22 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	set_info(t_phil *info, t_input *input)
{
	info->index = input->index + 1;
	info->nr_phil = input->gen_var->nr_phil;
	info->t_start = input->gen_var->t_start;
	info->last_meal = &input->gen_var->last_meals[input->index];
	*info->last_meal = get_time(&input->gen_var->time, input->gen_var->t_start);
	info->nr_meals = &input->gen_var->nr_meals[input->index];
	*info->nr_meals = 0;
	info->t_eat = input->gen_var->t_eat;
	info->t_sleep = input->gen_var->t_sleep;
	info->end = &input->gen_var->end;
	info->time = &input->gen_var->time;
	info->l_fork = &input->gen_var->forks[input->index];
	if (info->index < input->gen_var->nr_phil)
		info->r_fork = &input->gen_var->forks[info->index];
	else
		info->r_fork = &input->gen_var->forks[0];
}

void	*leftie_phil(void *data)
{
	t_phil	info;

	set_info(&info, data);
	if (info.index % 2 == 0)
		usleep(100);
	while (!*info.end)
	{
		pthread_mutex_lock(info.l_fork);
		if (*info.end)
			break ;
		printf("[%09d] %d %s\n", get_time(info.time, info.t_start), info.index, FORK);
		pthread_mutex_lock(info.r_fork);
		if (*info.end)
			break ;
		printf("[%09d] %d %s\n", get_time(info.time, info.t_start), info.index, FORK);
		*info.last_meal = get_time(info.time, info.t_start);
		if (*info.end)
			break ;
		printf("[%09d] %d %s\n", get_time(info.time, info.t_start), info.index, EATING);
		no_usleep(info.time, info.t_eat, info.nr_phil);
		*info.nr_meals += 1;
		pthread_mutex_unlock(info.l_fork);
		pthread_mutex_unlock(info.r_fork);
		if (*info.end)
			break ;
		printf("[%09d] %d %s\n", get_time(info.time, info.t_start), info.index, SLEEPING);
		no_usleep(info.time, info.t_sleep, info.nr_phil);
		if (*info.end)
			break ;
		printf("[%09d] %d %s\n", get_time(info.time, info.t_start), info.index, THINKING);
	}
	return (NULL);
}

void	phil_bonus_sp(int ind, t_gen *gen_var)
{
	pthread_t	phil;
	int			last_meal;
	int			nr_meals;
	
}

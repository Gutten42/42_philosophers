/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_func_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:35:02 by vgutten           #+#    #+#             */
/*   Updated: 2022/04/26 15:21:42 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	set_info(t_phil *info, t_input *input)
{
	info->index = input->index + 1;
	info->nr_phil = input->gen_var->nr_phil;
	info->t_start = input->gen_var->t_start;
	info->last_meal = input->last_meal;
	info->nr_meals = 0;
	info->max_meals = input->gen_var->max_meals;
	info->t_eat = input->gen_var->t_eat;
	info->t_sleep = input->gen_var->t_sleep;
	info->t_start = input->gen_var->t_start;
	info->forks = input->gen_var->forks;
	info->bowl = input->gen_var->bowl;
	info->sat = input->gen_var->sat;
	info->time = &input->gen_var->time;
}

void	*leftie_phil(void *data)
{
	t_phil	info;

	set_info(&info, data);
	while (1)
	{
		sem_wait(info.bowl);
		sem_wait(info.forks);
		printf("[%09d] %d %s\n", get_time(info.time, info.t_start), info.index, FORK);
		sem_wait(info.forks);
		printf("[%09d] %d %s\n", get_time(info.time, info.t_start), info.index, FORK);
		*info.last_meal = get_time(info.time, info.t_start);
		printf("[%09d] %d %s\n", get_time(info.time, info.t_start), info.index, EATING);
		no_usleep(info.time, info.t_eat, info.nr_phil);
		info.nr_meals++;
		if (info.nr_meals == info.max_meals)
			sem_post(info.sat);
		sem_post(info.forks);
		sem_post(info.forks);
		sem_post(info.bowl);
		printf("[%09d] %d %s\n", get_time(info.time, info.t_start), info.index, SLEEPING);
		no_usleep(info.time, info.t_sleep, info.nr_phil);
		printf("[%09d] %d %s\n", get_time(info.time, info.t_start), info.index, THINKING);
	}
	return (NULL);
}

void	phil_bonus_sp(int ind, t_gen *gen_var)
{
	pthread_t	phil;
	t_input		input;
	int			last_meal;
	int			ima;
	
	input.gen_var = gen_var;
	input.index = ind;
	last_meal = get_time(&gen_var->time, gen_var->t_start);
	input.last_meal = &last_meal;
	pthread_create(&phil, NULL, leftie_phil, &input);
	while (1)
	{
		ima = get_time(&gen_var->time, gen_var->t_start);
		if ((ima - gen_var->t_die) > last_meal)
			exit(0);
		usleep(gen_var->nr_phil);
	}
}

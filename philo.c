/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:03:52 by vguttenb          #+#    #+#             */
/*   Updated: 2022/04/26 19:03:33 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	nice_exit(t_gen *gen_var, int time, int index)
{
	int		ind;

	if (index)
	{
		no_usleep(&gen_var->time, 2, 10);
		printf("[%09d] %03d died\n", time, index);
	}
	ind = 0;
	while (ind < gen_var->nr_phil)
	{
		pthread_join(gen_var->minds[ind++], NULL);
		//printf("%d exited\n", ind);
	}
	ind = 0;
	while (ind < gen_var->nr_phil)
		pthread_mutex_destroy(&gen_var->forks[ind++]);
	pthread_mutex_destroy(&gen_var->print);
	free(gen_var->forks);
	free(gen_var->minds);
	free(gen_var->last_meals);
	free(gen_var->nr_meals);
	free(gen_var->input);
	exit(0);
}

void	check_phils(t_gen *gen_var)
{
	int	ima;
	int	ind;

	ima = get_time(&gen_var->time, gen_var->t_start) - gen_var->t_die;
	ind = 0;
	while (ind < gen_var->nr_phil)
	{
		if (gen_var->last_meals[ind] < ima)
		{
			gen_var->end = 1;
			nice_exit(gen_var, ima + gen_var->t_die, ind + 1);
		}
		ind++;
	}
}

void	check_max_meals(t_gen *gen_var)
{
	int	ind;

	ind = 0;
	while (ind < gen_var->nr_phil)
	{
		if (gen_var->nr_meals[ind] < gen_var->max_meals)
			return ;
		ind++;
	}
	gen_var->end = 1;
	nice_exit(gen_var, 0, 0);
}

void	set_gen_arrays(t_gen *gen_var)
{
	int	ind;

	gen_var->last_meals = (int *)malloc(sizeof(int) * gen_var->nr_phil);
	gen_var->nr_meals = (int *)malloc(sizeof(int) * gen_var->nr_phil);
	gen_var->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
						* gen_var->nr_phil);
	gen_var->minds = (pthread_t *)malloc(sizeof(pthread_t) * gen_var->nr_phil);
	pthread_mutex_init(&gen_var->print, NULL);
	ind = 0;
	while (ind < gen_var->nr_phil)
		pthread_mutex_init(&gen_var->forks[ind++], NULL);
}

int	main(int argc, char **argv)
{
	t_gen			gen_var;

	set_gen_var(&gen_var, argc, argv);
	set_gen_arrays(&gen_var);
	gen_var.t_start = get_time(&gen_var.time, 0);
	gen_var.end = 0;
	setup_phils(&gen_var);
	if (gen_var.max_meals)
	{
		while (1)
		{
			no_usleep(&gen_var.time, 1, gen_var.nr_phil);
			check_phils(&gen_var);
			check_max_meals(&gen_var);
		}
	}
	while (1)
	{
		no_usleep(&gen_var.time, 1, gen_var.nr_phil);
		check_phils(&gen_var);
	}
}

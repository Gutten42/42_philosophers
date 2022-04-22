/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:03:52 by vguttenb          #+#    #+#             */
/*   Updated: 2022/04/22 16:07:10 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* void	*thread_st(void *mutex)
{
	if (pthread_mutex_lock((pthread_mutex_t *)mutex) != 0)
		perror("pthread_mutex_lock");
	printf("Hi! I am a new thread and I've just been created\n");
	if (pthread_mutex_unlock((pthread_mutex_t *)mutex) != 0)
		perror("pthread_mutex_unlock");
	return (NULL);
}

void	*thread_wt(void *mutex)
{
	int				sec;
	
	sec = 3;
	printf("Hi! I am the waiting thread and I'm going to make the other thread wait\n");
	if (pthread_mutex_lock((pthread_mutex_t *)mutex) != 0)
		perror("pthread_mutex_lock");
	while (sec-- > 0)
	{
		printf("wait...\n");
		usleep(1000000);
	}
	if (pthread_mutex_unlock((pthread_mutex_t *)mutex) != 0)
		perror("pthread_mutex_unlock");
	return (NULL);
} */

void	nice_exit(t_gen *gen_var)
{
	int		ind;
	
	ind = 0;
	while (ind < gen_var->nr_phil)
	{
		pthread_mutex_destroy(&gen_var->forks[ind]);
		pthread_detach(gen_var->minds[ind]);
		ind++;
	}
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
	while(ind < gen_var->nr_phil)
	{
		if (gen_var->last_meals[ind] < ima)
		{
			gen_var->end = 1;
			printf("[%09d] %d died\n", ima + gen_var->t_die, ind + 1);
			nice_exit(gen_var);
			// pthread_mutex_unlock(&gen_var->pr_mutex);
			// pthread_mutex_destroy(&gen_var->pr_mutex);
			// printf("%d %d died\n", ima, phil_list->index);
			// usleep(1000000);
			//pthread_join(phil_list->mind, NULL);
			//exit(0);
		}
		ind++;
	}
}

void	check_max_meals(t_gen *gen_var)
{
	int	ind;

	ind = 0;
	while(ind < gen_var->nr_phil)
	{
		if (gen_var->nr_meals[ind] < gen_var->max_meals)
		{
			return ;
			// pthread_mutex_unlock(&gen_var->pr_mutex);
			// pthread_mutex_destroy(&gen_var->pr_mutex);
			// printf("%d %d died\n", ima, phil_list->index);
			// usleep(1000000);
			//pthread_join(phil_list->mind, NULL);
			//exit(0);
		}
		ind++;
	}
	gen_var->end = 1;
	nice_exit(gen_var);
}

void	set_gen_arrays(t_gen *gen_var)
{
	int	ind;
	
	gen_var->last_meals = (int *)malloc(sizeof(int) * gen_var->nr_phil);
	gen_var->nr_meals = (int *)malloc(sizeof(int) * gen_var->nr_phil);
	gen_var->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * gen_var->nr_phil);
	gen_var->minds = (pthread_t *)malloc(sizeof(pthread_t) * gen_var->nr_phil);
	ind = 0;
	while (ind < gen_var->nr_phil)
		pthread_mutex_init(&gen_var->forks[ind++], NULL);
}

int	main(int argc, char **argv)
{
	t_gen			gen_var;
/* 	pthread_t		thread1;
	pthread_t		thread2;
	pthread_mutex_t	mutex; */
	
	set_gen_var(&gen_var, argc, argv);
	set_gen_arrays(&gen_var);
	printf("I have received %d nr of philosophers, %d, time to die, %d time to eat and %d time to sleep\n", gen_var.nr_phil, gen_var.t_die, gen_var.t_eat, gen_var.t_sleep);
	gen_var.t_start = get_time(&gen_var.time, 0);
	gen_var.end = 0;
	setup_phils(&gen_var);
	if (gen_var.max_meals)
	{
		while(1)
		{
			no_usleep(&gen_var.time, 1, gen_var.nr_phil);
			check_phils(&gen_var);
			check_max_meals(&gen_var);
		}
	}
	while(1)
	{
		no_usleep(&gen_var.time, 1, gen_var.nr_phil);
		check_phils(&gen_var);
	}
	
/* 	printf("Hi there world, I'm philo and I am going to create a new thread\n");
	if (pthread_mutex_init(&mutex, NULL) != 0)
		printf("Oh no! Something must've gone wrong at mutex init\n");
	if (pthread_create(&thread2, NULL, thread_wt, &mutex) != 0)
		printf("Oh no! Something must've gone wrong at creation of thread 2\n");
	if (pthread_create(&thread1, NULL, thread_st, &mutex) != 0)
		printf("Oh no! Something must've gone wrong at creation of thread 1\n");
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	if (pthread_mutex_destroy(&mutex) != 0)
		printf("Oh no! Something must've gone wrong at mutex destry\n"); */
}
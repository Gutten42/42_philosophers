/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgutten <vgutten@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:03:52 by vguttenb          #+#    #+#             */
/*   Updated: 2022/04/19 12:43:01 by vgutten          ###   ########.fr       */
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

void	check_phils(t_phil *phil_list, t_gen *gen_var)
{
	int	ima;

	while(1)
	{
		ima = get_time(&gen_var->time);
		if (phil_list->last_meal < ima - gen_var->t_die)
		{
			gen_var->end = 1;
			pthread_mutex_unlock(&gen_var->pr_mutex);
			pthread_mutex_destroy(&gen_var->pr_mutex);
			printf("%d %d died\n", ima, phil_list->index);
			usleep(1000000);
			//pthread_join(phil_list->mind, NULL);
			exit(0);
		}
		phil_list = phil_list->next;
		if (phil_list->index == 1)
			break ;
	}
}

int	main(int argc, char **argv)
{
	t_gen			gen_var;
	t_phil			*phil_list;
/* 	pthread_t		thread1;
	pthread_t		thread2;
	pthread_mutex_t	mutex; */
	
	set_gen_var(&gen_var, argc, argv);
	printf("I have received %d nr of philosophers, %d, time to die, %d time to eat and %d time to sleep\n", gen_var.nr_phil, gen_var.t_die, gen_var.t_eat, gen_var.t_sleep);
	pthread_mutex_init(&gen_var.pr_mutex, NULL);
	gettimeofday(&gen_var.time, NULL);
	gen_var.end = 0;
	phil_list = setup_phils(&gen_var);
	while(1)
	{
		check_phils(phil_list, &gen_var);
		//usleep(gen_var.nr_of_phil);
		no_usleep(&gen_var.time, 10, gen_var.nr_phil);
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
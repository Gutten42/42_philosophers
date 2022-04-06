/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:03:52 by vguttenb          #+#    #+#             */
/*   Updated: 2022/04/06 19:51:45 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_st(void *mutex)
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
}

int	phil_atoi(char *str)
{
	long	ret;

	ret = 0;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		ret = ret * 10 + (*str++ - '0');
		if (ret > INT_MAX)
			return (0);
	}
	return ((int)ret);
}

int	set_var(int *var, char *value_str)
{
	int	value;

	value = phil_atoi(value_str);
	if (value < 1)
		return (0);
	*var = value;
	return (1);
}

void	set_gen_var(t_gen *gen_var, int argc, char **argv)
{
	char	*err;

	err = NULL;
	if (argc < 5)
		err = "not enough arguments provided";
	else if (argc > 6)
		err = "too many arguments provided";
	else if (!err && !set_var(&gen_var->nr_of_phil, argv[1]))
		err = "incompatible number of philosophers provided";
	else if (!err && !set_var(&gen_var->time_to_die, argv[2]))
		err = "incompatible time to die provided";
	else if (!err && !set_var(&gen_var->time_to_eat, argv[3]))
		err = "incompatible time to eat provided";
	else if (!err && !set_var(&gen_var->time_to_sleep, argv[4]))
		err = "incompatible time to sleep provided";
	else if (argc > 5 && !err && !set_var(&gen_var->nr_of_meals, argv[5]))
		err = "incompatible number of times each philosopher must eat provided";
	else
		gen_var->nr_of_meals = 0;
	if (err)
	{
		ft_putstr_fd("philo: error: ", STDERR_FILENO);
		ft_putendl_fd(err, STDERR_FILENO);
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	t_gen			gen_var;
	pthread_t		thread1;
	pthread_t		thread2;
	pthread_mutex_t	mutex;
	
	set_gen_var(&gen_var, argc, argv);
	printf("Hi there world, I'm philo and I am going to create a new thread\n");
	if (pthread_mutex_init(&mutex, NULL) != 0)
		printf("Oh no! Something must've gone wrong at mutex init\n");
	if (pthread_create(&thread2, NULL, thread_wt, &mutex) != 0)
		printf("Oh no! Something must've gone wrong at creation of thread 2\n");
	if (pthread_create(&thread1, NULL, thread_st, &mutex) != 0)
		printf("Oh no! Something must've gone wrong at creation of thread 1\n");
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	if (pthread_mutex_destroy(&mutex) != 0)
		printf("Oh no! Something must've gone wrong at mutex destry\n");
}
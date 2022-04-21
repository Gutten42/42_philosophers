/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_func_log_nou.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:35:02 by vgutten           #+#    #+#             */
/*   Updated: 2022/04/21 16:30:09 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	*leftie_phil(void *data)
// {
// 	t_phill	*info;

// 	info = (t_phill *)data;
// 	if (info->index % 2 == 0)
// 	  	usleep(100);
// 	//printf("I am a left philosopher with index %d\n", info->index);
// 	log_state(&info->gen_var->print_right, get_time(&info->gen_var->time), info->index, " is born");
// 	while (1)
// 	{
// 		if (pthread_mutex_lock(&info->l_fork) != 0)
// 			perror("pthread_mutex_lock");
// 		// if (info->gen_var->end)
// 			// break ;
// 		log_state(&info->gen_var->print_right, get_time(&info->gen_var->time), info->index, FORK);
// 		if (pthread_mutex_lock(&info->next->l_fork) != 0)
// 			perror("pthread_mutex_lock");
// 		// if (info->gen_var->end)
// 			// break ;
// 		log_state(&info->gen_var->print_right, get_time(&info->gen_var->time), info->index, FORK);
// 		info->last_meal = get_time(&info->gen_var->time);
// 		log_state(&info->gen_var->print_right, get_time(&info->gen_var->time), info->index, EATING);
// 		no_usleep(info->gen_var->time_to_eat, info->gen_var->nr_of_phil, &info->gen_var->time);
// 		if (pthread_mutex_unlock(&info->l_fork) != 0)
// 			perror("pthread_mutex_unlock");
// 		if (pthread_mutex_unlock(&info->next->l_fork) != 0)
// 			perror("pthread_mutex_unlock");
// 		// if (info->gen_var->end)
// 			// break ;
// 		log_state(&info->gen_var->print_right, get_time(&info->gen_var->time), info->index, SLEEPING);
// 		no_usleep(info->gen_var->time_to_sleep, info->gen_var->nr_of_phil, &info->gen_var->time);
// 		// if (info->gen_var->end)
// 			// break ;
// 		log_state(&info->gen_var->print_right, get_time(&info->gen_var->time), info->index, THINKING);
// 		// if (info->gen_var->end)
// 			// break ;
// 	}
// 	return(NULL);
// }

void	set_info(t_phil *info, t_input *input)
{
	info->index = input->index + 1;
	info->nr_phil = input->gen_var->nr_phil;
	info->last_meal = &input->gen_var->last_meals[input->index];
	*info->last_meal = get_time(&input->gen_var->time);
	info->nr_meals = &input->gen_var->nr_meals[input->index];
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
	//printf("%d %d %s\n", get_time(info.time), info.index, "is born");
	while (!*info.end)
	{
		pthread_mutex_lock(info.l_fork);
		if (*info.end)
			break ;
		printf("%d %d %s\n", get_time(info.time), info.index, FORK);
		pthread_mutex_lock(info.r_fork);
		if (*info.end)
			break ;
		printf("%d %d %s\n", get_time(info.time), info.index, FORK);
		*info.last_meal = get_time(info.time);
		if (*info.end)
			break ;
		printf("%d %d %s\n", get_time(info.time), info.index, EATING);
		no_usleep(info.time, info.t_eat, info.nr_phil);
		pthread_mutex_unlock(info.l_fork);
		pthread_mutex_unlock(info.r_fork);
		if (*info.end)
			break ;
		printf("%d %d %s\n", get_time(info.time), info.index, SLEEPING);
		no_usleep(info.time, info.t_sleep, info.nr_phil);
		if (*info.end)
			break ;
		printf("%d %d %s\n", get_time(info.time), info.index, THINKING);
	}
	return (NULL);
}

/* void	*rightie_phil(void *data)
{
	t_phill	*info;

	info = (t_phill *)data;
	log_state(&info->gen_var->print_right, get_time(&info->gen_var->time), info->index, " is born");
	while (1)
	{
		if (pthread_mutex_lock(&info->next->l_fork) != 0)
			perror("pthread_mutex_lock");
		// if (info->gen_var->end)
			// break ;
		log_state(&info->gen_var->print_right, get_time(&info->gen_var->time), info->index, FORK);
		if (pthread_mutex_lock(&info->l_fork) != 0)
			perror("pthread_mutex_lock");
		// if (info->gen_var->end)
			// break ;
		log_state(&info->gen_var->print_right, get_time(&info->gen_var->time), info->index, FORK);
		log_state(&info->gen_var->print_right, get_time(&info->gen_var->time), info->index, EATING);
		info->last_meal = get_time(&info->gen_var->time);
		no_usleep(info->gen_var->time_to_eat, info->gen_var->nr_of_phil, &info->gen_var->time);
		if (pthread_mutex_unlock(&info->next->l_fork) != 0)
			perror("pthread_mutex_unlock");
		if (pthread_mutex_unlock(&info->l_fork) != 0)
			perror("pthread_mutex_unlock");
		// if (info->gen_var->end)
			// break ;
		log_state(&info->gen_var->print_right, get_time(&info->gen_var->time), info->index, SLEEPING);
		no_usleep(info->gen_var->time_to_sleep, info->gen_var->nr_of_phil, &info->gen_var->time);
		// if (info->gen_var->end)
			// break ;
		log_state(&info->gen_var->print_right, get_time(&info->gen_var->time), info->index, THINKING);
		// if (info->gen_var->end)
			// break ;
	}
	return(NULL);
}
 */
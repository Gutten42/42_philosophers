/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgutten <vgutten@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:35:02 by vgutten           #+#    #+#             */
/*   Updated: 2022/04/14 21:51:06 by vgutten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*leftie_phil(void *data)
{
	t_phill	*info;

	info = (t_phill *)data;
	printf("I am a left philosopher with index %d\n", info->index);
	while (1)
	{
		if (info->dead)
			break ;
		if (pthread_mutex_lock(&info->l_fork) != 0)
			perror("pthread_mutex_lock");
		if (info->dead)
			break ;
		printf("%d %d has taken a fork\n", get_time(&info->gen_var->time), info->index);
		if (pthread_mutex_lock(&info->next->l_fork) != 0)
			perror("pthread_mutex_lock");
		if (info->dead)
			break ;
		printf("%d %d has taken a fork\n", get_time(&info->gen_var->time), info->index);
		printf("%d %d is eating\n", get_time(&info->gen_var->time), info->index);
		info->last_meal = get_time(&info->gen_var->time);
		usleep(info->gen_var->time_to_eat * 1000);
		if (info->dead)
			break ;
		if (pthread_mutex_unlock(&info->l_fork) != 0)
			perror("pthread_mutex_unlock");
		if (pthread_mutex_unlock(&info->next->l_fork) != 0)
			perror("pthread_mutex_unlock");
		printf("%d %d is sleeping\n", get_time(&info->gen_var->time), info->index);
		usleep(info->gen_var->time_to_sleep * 1000);
		if (info->dead)
			break ;
		printf("%d %d is thinking\n", get_time(&info->gen_var->time), info->index);
	}
	return(NULL);
}

void	*rightie_phil(void *data)
{
	t_phill	*info;

	info = (t_phill *)data;
	printf("I am a right philosopher with index %d\n", info->index);
	while (1)
	{
		if (info->dead)
			break ;
		if (pthread_mutex_lock(&info->next->l_fork) != 0)
			perror("pthread_mutex_lock");
		if (info->dead)
			break ;
		printf("%d %d has taken a fork\n", get_time(&info->gen_var->time), info->index);
		if (pthread_mutex_lock(&info->l_fork) != 0)
			perror("pthread_mutex_lock");
		if (info->dead)
			break ;
		printf("%d %d has taken a fork\n", get_time(&info->gen_var->time), info->index);
		printf("%d %d is eating\n", get_time(&info->gen_var->time), info->index);
		info->last_meal = get_time(&info->gen_var->time);
		usleep(info->gen_var->time_to_eat * 1000);
		if (info->dead)
			break ;
		if (pthread_mutex_unlock(&info->next->l_fork) != 0)
			perror("pthread_mutex_unlock");
		if (pthread_mutex_unlock(&info->l_fork) != 0)
			perror("pthread_mutex_unlock");
		printf("%d %d is sleeping\n", get_time(&info->gen_var->time), info->index);
		usleep(info->gen_var->time_to_sleep * 1000);
		if (info->dead)
			break ;
		printf("%d %d is thinking\n", get_time(&info->gen_var->time), info->index);
	}
	return(NULL);
}

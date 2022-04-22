/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 20:49:58 by vgutten           #+#    #+#             */
/*   Updated: 2022/04/21 16:59:12 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_state(pthread_mutex_t *print_right, int timestamp, int index, char *state)
{
/* 	if (!pthread_mutex_lock(print_right))
	{
		printf("%d %d %s\n", timestamp, index, state);
		pthread_mutex_unlock(print_right);
	} */
	//pthread_mutex_lock(print_right);
	printf("%d %d %s\n", timestamp, index, state);
	//pthread_mutex_unlock(print_right);
/* 	ft_putnbr_fd(timestamp, STDOUT_FILENO);
	ft_putchar_fd(' ', STDOUT_FILENO);
	ft_putnbr_fd(index, STDOUT_FILENO);
	ft_putendl_fd(state, STDOUT_FILENO); */
	(void)print_right;
}
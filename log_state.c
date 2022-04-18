/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 20:49:58 by vgutten           #+#    #+#             */
/*   Updated: 2022/04/18 15:48:27 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_state(pthread_mutex_t *print_right, int timestamp, int index, char *state)
{
	pthread_mutex_lock(print_right);
	ft_putnbr_fd(timestamp, STDOUT_FILENO);
	ft_putchar_fd(' ', STDOUT_FILENO);
	ft_putnbr_fd(index, STDOUT_FILENO);
	ft_putendl_fd(state, STDOUT_FILENO);
	pthread_mutex_unlock(print_right);
}
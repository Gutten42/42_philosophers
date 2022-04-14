/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgutten <vgutten@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 20:49:58 by vgutten           #+#    #+#             */
/*   Updated: 2022/04/14 21:35:38 by vgutten          ###   ########.fr       */
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
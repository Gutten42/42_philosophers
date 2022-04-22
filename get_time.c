/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:29:50 by vgutten           #+#    #+#             */
/*   Updated: 2022/04/22 15:52:40 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(struct timeval *time, int t_start)
{
	gettimeofday(time, NULL);
	return ((time->tv_sec * 1000 + time->tv_usec / 1000) - t_start);
}

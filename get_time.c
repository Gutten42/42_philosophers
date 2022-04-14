/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgutten <vgutten@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:29:50 by vgutten           #+#    #+#             */
/*   Updated: 2022/04/14 18:47:21 by vgutten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(struct timeval *time)
{
	gettimeofday(time, NULL);
	//printf("Here it's %ld\n", time->tv_usec);
	return (time->tv_sec * 1000 + time->tv_usec / 1000);
}
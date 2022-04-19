/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgutten <vgutten@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 21:58:46 by vgutten           #+#    #+#             */
/*   Updated: 2022/04/19 11:55:55 by vgutten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	no_usleep(struct timeval *time, int wait, int cadency)
{
	int	deadline;

	deadline = get_time(time) + wait;
	while (1)
	{
		if (get_time(time) >= deadline)
			return ;
		usleep(cadency);
	}
}
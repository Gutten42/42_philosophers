/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 21:58:46 by vgutten           #+#    #+#             */
/*   Updated: 2022/04/22 15:56:33 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	no_usleep(struct timeval *time, int wait, int cadency)
{
	int	deadline;

	deadline = get_time(time, 0) + wait;
	while (1)
	{
		if (get_time(time, 0) >= deadline)
			return ;
		usleep(cadency);
	}
}
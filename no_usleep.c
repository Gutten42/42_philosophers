/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgutten <vgutten@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 21:58:46 by vgutten           #+#    #+#             */
/*   Updated: 2022/04/14 22:15:18 by vgutten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	no_usleep(int wait, int cadency, struct timeval *time)
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:40:56 by vguttenb          #+#    #+#             */
/*   Updated: 2022/04/26 16:27:11 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_nbr(char *print, int time, int index)
{
	int	ind;

	print[0] = '[';
	ind = 9;
	while (ind > 0 )
	{
		print[ind--] = time % 10 + '0';
		time /= 10;
	}
	print[10] = ']';
	print[11] = ' ';
	ind = 14;
	while (ind > 11)
	{
		print[ind--] = index % 10 + '0';
		index /= 10;
	}
	print[15] = ' ';
}

static void	set_str(char *print, char *state)
{
	while (*state)
		*print++ = *state++;
	*print++ = '\n';
	*print = '\0';
}

int	log_state(t_phil *info, int code)
{
	int		str_size;
	char	*print;

	if (*info->end)
		return(0);
	pthread_mutex_lock(info->print);
	if (code > 2)
		str_size = 11 + 17;
	else if (code == 2)
		str_size = 9 + 17;
	else
		str_size = 16 + 17;
	print = (char *)malloc(sizeof(char) * str_size + 1);
	set_nbr(print, get_time(info->time, info->t_start), info->index);
	if (code == 1)
		set_str(&print[16], "has taken a fork");
	if (code == 2)
		set_str(&print[16], "is eating");
	if (code == 3)
		set_str(&print[16], "is sleeping");
	if (code == 4)
		set_str(&print[16], "is thinking");
	write(STDOUT_FILENO, print, str_size);
	pthread_mutex_unlock(info->print);
	return(1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_gen_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:33:18 by vgutten           #+#    #+#             */
/*   Updated: 2022/04/18 16:12:13 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	phil_atoi(char *str)
{
	long	ret;

	ret = 0;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		ret = ret * 10 + (*str++ - '0');
		if (ret > INT_MAX)
			return (0);
	}
	return ((int)ret);
}

static int	set_var(int *var, char *value_str)
{
	int	value;

	value = phil_atoi(value_str);
	if (value < 1)
		return (0);
	*var = value;
	return (1);
}

void	set_gen_var(t_gen *gen_var, int argc, char **argv)
{
	char	*err;

	err = NULL;
	if (argc < 5)
		err = "not enough arguments provided";
	else if (argc > 6)
		err = "too many arguments provided";
	else if (!err && !set_var(&gen_var->nr_of_phil, argv[1]))
		err = "incompatible number of philosophers provided";
	else if (!err && !set_var(&gen_var->time_to_die, argv[2]))
		err = "incompatible time to die provided";
	else if (!err && !set_var(&gen_var->time_to_eat, argv[3]))
		err = "incompatible time to eat provided";
	else if (!err && !set_var(&gen_var->time_to_sleep, argv[4]))
		err = "incompatible time to sleep provided";
	else if (argc > 5 && !err && !set_var(&gen_var->max_meals, argv[5]))
		err = "incompatible number of times each philosopher must eat provided";
	else if (argc == 5)
		gen_var->max_meals = 0;
	if (err)
	{
		ft_putstr_fd("philo: error: ", STDERR_FILENO);
		ft_putendl_fd(err, STDERR_FILENO);
		exit(1);
	}
}

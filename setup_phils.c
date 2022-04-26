/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_phils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:00:29 by vgutten           #+#    #+#             */
/*   Updated: 2022/04/26 15:04:57 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	setup_phils(t_gen *gen_var)
{
	int		ind;

	gen_var->input = (t_input *)malloc(sizeof(t_input) * gen_var->nr_phil);
	ind = 0;
	while (ind < gen_var->nr_phil)
	{
		gen_var->input[ind].index = ind;
		gen_var->input[ind].gen_var = gen_var;
		ind++;
	}
	ind = 0;
	while (ind < gen_var->nr_phil)
	{
		pthread_create(&gen_var->minds[ind], NULL, \
						leftie_phil, &gen_var->input[ind]);
		ind++;
	}
}

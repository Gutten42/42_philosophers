/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release_the_phils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:31:50 by vgutten           #+#    #+#             */
/*   Updated: 2022/04/26 15:05:47 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_phill	*create_phil(t_gen *gen_var, int ind)
{
	t_phill	*node;

	node = (t_phill *)malloc(sizeof(t_phill));
	ft_bzero(node, sizeof(t_phill));
	node->index = ind;
	node->last_meal = get_time(&gen_var->time);
	pthread_mutex_init(&node->l_fork, NULL);
	node->gen_var = gen_var;
	return (node);
}

t_phill	*release_the_phils(t_gen *gen_var)
{
	int		ind;
	t_phill	*first;
	t_phill	*iter;

	ind = 1;
	first = create_phil(gen_var, ind++);
	iter = first;
	while (ind <= gen_var->nr_of_phil)
	{
		iter->next = create_phil(gen_var, ind++);
		iter = iter->next;
	}
	iter->next = first;
	while (1)
	{
		pthread_create(&first->mind, NULL, leftie_phil, first);
		first = first->next;
		if (first->index == 1)
			break ;
	}
	return (first);
}

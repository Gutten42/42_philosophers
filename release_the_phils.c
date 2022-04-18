/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release_the_phils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:31:50 by vgutten           #+#    #+#             */
/*   Updated: 2022/04/18 16:41:15 by vguttenb         ###   ########.fr       */
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
//	printf("I'm gonna create a philosopher with %d index, and %d last meal with data at%p\n", node->index, node->last_meal, node);
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
//	printf("I'm gonna create %d philosophers\n", gen_var->nr_of_phil);
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
		if (first->index % 2)
			pthread_create(&first->mind, NULL, leftie_phil, first);
		else
			pthread_create(&first->mind, NULL, rightie_phil, first);
		// if (first->index % 2 == 0)
		// 	usleep(100);
		pthread_create(&first->mind, NULL, leftie_phil, first);
		first = first->next;
		if (first->index == 1)
			break ;
	}
	return (first);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_phils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgutten <vgutten@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:00:29 by vgutten           #+#    #+#             */
/*   Updated: 2022/04/19 11:59:55 by vgutten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_phil	*create_phil(t_gen *gen_var, int ind)
{
	t_phil	*node;

	node = (t_phil *)malloc(sizeof(t_phil));
	node->index = ind;
	node->nr_meals = 0;
	node->max_meals = gen_var->max_meals;
	node->t_eat = gen_var->t_eat;
	node->t_sleep = gen_var->t_sleep;
	node->end = &gen_var->end;
	node->pr_mutex = &gen_var->pr_mutex;
	pthread_mutex_init(&node->fork, NULL);
	node->l_fork = &node->fork;
	node->time = &gen_var->time;
	return(node);
}

void	release_the_phils(t_phil *first)
{
	while (1)
	{
		first->last_meal = get_time(first->time);
		pthread_create(&first->mind, NULL, leftie_phil, first);
		first = first->next;
		if (first->index == 1)
			return ;
	}
}

t_phil	*setup_phils(t_gen *gen_var)
{
	int		ind;
	t_phil	*first;
	t_phil	*iter;

	ind = 1;
	first = create_phil(gen_var, ind++);
	iter = first;
	while (ind <= gen_var->nr_phil)
	{
		iter->next = create_phil(gen_var, ind++);
		iter->r_fork = &iter->next->fork;
		iter = iter->next;
	}
	iter->r_fork = &first->fork;
	iter->next = first;
	release_the_phils(first);
	return (first);
}
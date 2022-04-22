/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:03:52 by vguttenb          #+#    #+#             */
/*   Updated: 2022/04/22 19:32:37 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	nice_exit(t_gen *gen_var, int sp_count)
{
	int		ind;
	
	ind = 0;
	while (ind < sp_count)
		waitpid(gen_var->minds[ind], NULL, 0);
	sem_unlink("semie");
	free(gen_var->minds);
	free(gen_var->last_meals);
	free(gen_var->nr_meals);
	exit(0);
}

void	check_phils(t_gen *gen_var)
{
	int	ima;
	int	ind;

	ima = get_time(&gen_var->time, gen_var->t_start) - gen_var->t_die;
	printf("I am the checker and I am going to check for %d\n", ima);
	ind = 0;
	while(ind < gen_var->nr_phil)
	{
		if (gen_var->last_meals[ind] < ima)
		{
			gen_var->end = 1;
			printf("[%09d] %d died\n", ima + gen_var->t_die, ind + 1);
			printf("cause he last ate at %d\n", gen_var->last_meals[ind]);
			nice_exit(gen_var, gen_var->nr_phil);
		}
		ind++;
	}
}

void	check_max_meals(t_gen *gen_var)
{
	int	ind;

	ind = 0;
	while(ind < gen_var->nr_phil)
	{
		if (gen_var->nr_meals[ind] < gen_var->max_meals)
			return ;
		ind++;
	}
	gen_var->end = 1;
	nice_exit(gen_var, gen_var->nr_phil);
}

void	set_gen_arrays(t_gen *gen_var)
{
	int	ind;
	
	gen_var->forks = sem_open("semie", O_CREAT, S_IRUSR | S_IWUSR, gen_var->nr_phil / 2);
	gen_var->minds = (pid_t *)malloc(sizeof(pid_t) * gen_var->nr_phil);
	ind = 0;
	while (ind < gen_var->nr_phil)
	{
		gen_var->minds[ind] = fork();
		if (gen_var->minds[ind] == 0)
			phil_bonus_sp(ind, gen_var);
		else if (gen_var->minds[ind] < 0)
		{
			perror("philo: fork");
			nice_exit(gen_var, ind);
		}
		ind++;
	}
}

int	main(int argc, char **argv)
{
	t_gen			gen_var;
	
	set_gen_var(&gen_var, argc, argv);
	printf("I have received %d nr of philosophers, %d, time to die, %d time to eat and %d time to sleep\n", gen_var.nr_phil, gen_var.t_die, gen_var.t_eat, gen_var.t_sleep);
	gen_var.t_start = get_time(&gen_var.time, 0);
	gen_var.end = 0;
	set_gen_arrays(&gen_var);
	write(STDERR_FILENO, "HEY\n", 4);
	if (gen_var.max_meals)
	{
		while(1)
		{
			no_usleep(&gen_var.time, 1, gen_var.nr_phil);
			check_phils(&gen_var);
			check_max_meals(&gen_var);
		}
	}
	while(1)
	{
		no_usleep(&gen_var.time, 1, gen_var.nr_phil);
		check_phils(&gen_var);
	}
}
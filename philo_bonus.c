/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:03:52 by vguttenb          #+#    #+#             */
/*   Updated: 2022/04/25 17:58:03 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	nice_exit(t_gen *gen_var, int last_pid)
{
	int		ind;
	
	ind = 0;
	while (ind < gen_var->nr_phil)
		kill(gen_var->minds[ind++], SIGTERM);
	sem_unlink("SEM_PHIL_SAT");
	sem_unlink("SEM_PHIL_FORKS");
	sem_unlink("SEM_PHIL_BOWL");
	ind = 0;
	if (last_pid)
		while (ind < gen_var->nr_phil)
			if (gen_var->minds[ind++] == last_pid)
				printf("[%09d] %d died\n", get_time(&gen_var->time, gen_var->t_start), ind);
	free(gen_var->minds);
	exit(0);
}

void	set_gen_arrays(t_gen *gen_var)
{
	int	ind;
	

	sem_unlink("SEM_PHIL_SAT");
	sem_unlink("SEM_PHIL_FORKS");
	sem_unlink("SEM_PHIL_BOWL");
	gen_var->sat = sem_open("SEM_PHIL_SAT", O_CREAT, 0660, 0);
	gen_var->forks = sem_open("SEM_PHIL_FORKS", O_CREAT, 0660, gen_var->nr_phil);
	gen_var->bowl = sem_open("SEM_PHIL_BOWL", O_CREAT, 0660, gen_var->nr_phil / 2 + gen_var->nr_phil % 2);
	gen_var->minds = (pid_t *)malloc(sizeof(pid_t) * gen_var->nr_phil);
	gen_var->t_start = get_time(&gen_var->time, 0);
	ind = 0;
	while (ind < gen_var->nr_phil)
	{
		gen_var->minds[ind] = fork();
		if (gen_var->minds[ind] == 0)
			phil_bonus_sp(ind, gen_var);
		else if (gen_var->minds[ind] < 0)
		{
			perror("philo: fork");
			nice_exit(gen_var, 0);
		}
		ind++;
	}
}

void	set_sat_checker(t_gen *gen_var)
{
	pid_t	sat_checker;
	int		ind;

	sat_checker = fork();
	if (sat_checker < 0)
	{
		perror("philosophers: fork");
		nice_exit(gen_var, 0);
	}
	if (sat_checker == 0)
	{
		ind = 0;
		while (ind++ < gen_var->nr_phil)
			sem_wait(gen_var->sat);
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	t_gen	gen_var;
	pid_t	last_pid;
	
	set_gen_var(&gen_var, argc, argv);
	printf("I have received %d nr of philosophers, %d, time to die, %d time to eat and %d time to sleep\n", gen_var.nr_phil, gen_var.t_die, gen_var.t_eat, gen_var.t_sleep);
	//gen_var.end = 0;
	set_gen_arrays(&gen_var);
	if (gen_var.max_meals)
		set_sat_checker(&gen_var);
	last_pid = waitpid(-1, NULL, 0);
	nice_exit(&gen_var, last_pid);
}
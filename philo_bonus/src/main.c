/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:31:20 by mlazzare          #+#    #+#             */
/*   Updated: 2021/11/09 18:00:33 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_philo(t_params *p, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < p->num)
	{
		philo[i].id = i;
		philo[i].dead = 0;
		philo[i].iter_num = 0;
		philo[i].thread_start = 0;
		philo[i].last_meal = 0;
		philo[i].params = p;
	}
	return (0);
}

static int	init_params_semaphore(t_params *p)
{
	p->death = 0;
	p->fork = 0;
	sem_unlink("/death");
	sem_unlink("/fork");
	p->death = sem_open("/death", O_CREAT, 0660, 1);
	if (p->death == SEM_FAILED)
		return (error_msg("Error\nDeath semaphore init failed\n", p, 0, 1));
	p->fork = sem_open("/fork", O_CREAT, 0660, p->num);
	if (p->fork == SEM_FAILED)
		return (error_msg("Error\nFork semaphore init failed\n", p, 0, 1));
	return (0);
}

static int	init_params(t_params *p, char **ag)
{
	int	sem;

	p->num = ft_atoi(ag[1]);
	p->forks = p->num;
	p->time2die = ft_atoi(ag[2]);
	p->time2eat = ft_atoi(ag[3]);
	p->time2sleep = ft_atoi(ag[4]);
	p->max_iter = 0;
	p->check_meal = 0;
	if (ag[5])
	{
		p->check_meal = 1;
		p->max_iter = ft_atoi(ag[5]);
	}
	p->over = 0;
	if (p->num > 0)
		sem = init_params_semaphore(p);
	return (sem || p->num < 0 || p->time2die < 0 || p->time2eat < 0
		|| p->time2sleep < 0 || p->max_iter < 0);
}

int	main(int ac, char **ag)
{
	t_params	p;

	memset(&p, 0, sizeof(p));
	if ((ac != 5 && ac != 6) || init_params(&p, ag))
		return (error_msg("Error: invalid arguments\n", &p, 0, 1));
	if (philosophers(&p))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

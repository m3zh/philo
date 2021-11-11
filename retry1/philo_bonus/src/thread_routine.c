/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:16:12 by mlazzare          #+#    #+#             */
/*   Updated: 2021/11/10 14:09:49 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	someone_died(long int now, t_philo *p, int unlock, int print)
{
	if (unlock)
	{
		sem_post(p->params->fork);
		sem_post(p->params->fork);
	}
	if (print)
	{
		print_routine(now, p, DIE);
		p->params->over = 1;
		p->dead = 1;
	}
	return (1);
}

int	check_death(t_philo *p)
{
	long int	now;

	now = time_now(p) - p->last_meal;
	sem_wait(p->params->death);
	if (now > p->params->time2die)
	{
		now = time_now(p) - p->thread_start;
		sem_post(p->params->death);
		return (someone_died(now, p, 1, 1));
	}
	sem_post(p->params->death);
	return (0);
}

int	ft_sleep_and_think(t_philo *p)
{
	long int	now;

	if (p->params->over)
		return (1);
	ft_usleep(p->params->time2sleep);
	now = time_now(p);
	print_routine(now - p->thread_start, p, SLEEP);
	print_routine(now - p->thread_start, p, THINK);
	if (p->params->over)
		return (1);
	if (now - p->last_meal > p->params->time2die)
		return (someone_died(now - p->thread_start, p, 0, 1));
	return (0);
}

int	ft_eat(t_philo *p)
{
	sem_wait(p->params->fork);
	if (print_routine(time_now(p) - p->thread_start, p, FORK))
		return (sem_post(p->params->fork) + 2);
	sem_wait(p->params->fork);
	if (print_routine(time_now(p) - p->thread_start, p, FORK))
		return (someone_died(time_now(p), p, 1, 1));
	p->last_meal = time_now(p);
	if (p->params->over)
	{
		sem_post(p->params->fork);
		sem_post(p->params->fork);
		return (1);
	}
	if (print_routine(time_now(p) - p->thread_start, p, EAT))
		return (someone_died(0, p, 1, 1));
	if (p->params->over)
		return (someone_died(0, p, 1, 0));
	ft_usleep(p->params->time2eat);
	p->iter_num++;
	sem_post(p->params->fork);
	sem_post(p->params->fork);
	return (0);
}

void	*thread_routine(void *job)
{
	int		starved;
	t_philo	*philo;

	starved = 0;
	philo = (t_philo *)job;
	if (philo->id & 1)
		ft_usleep(7);
	philo->thread_start = philo->params->start;
	philo->last_meal = time_now(philo);
	while (!starved && !philo->dead && !philo->params->over)
	{
		if (!starved)
			starved = ft_eat(philo);
		if (!starved && !philo->dead && !philo->params->over)
			starved = ft_sleep_and_think(philo);
	}
	return (NULL);
}

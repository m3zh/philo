/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:16:12 by mlazzare          #+#    #+#             */
/*   Updated: 2021/11/03 10:18:58 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	someone_died(long int now, t_philo *p)
{
	print_routine(now, p, DIE);
	p->params->over = 1;
	p->dead = 1;
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
	return (1);
}

int	check_death(t_philo *p)
{
	long int	now;

	now = time_now(p) - p->last_meal;
	pthread_mutex_lock(p->params->death);
	if (p->dead || now > p->params->time2die)
	{
		now = time_now(p) - p->thread_start;
		pthread_mutex_unlock(p->params->death);
		return (someone_died(now, p));
	}
	pthread_mutex_unlock(p->params->death);
	return (0);
}

int	ft_sleep_and_think(t_philo *p)
{
	long int	now;

	if (!p->params->over)
		ft_usleep(p->params->time2sleep);
	now = time_now(p);
	print_routine(now - p->thread_start, p, SLEEP);
	print_routine(now - p->thread_start, p, THINK);
	if (p->params->over)
		return (1);
	if (now - p->last_meal > p->params->time2die)
		return (someone_died(now - p->thread_start, p));
	return (0);
}

int	ft_eat(t_philo *p)
{
	pthread_mutex_lock(p->left_fork);
	if (print_routine(time_now(p) - p->thread_start, p, FORK))
	{
		pthread_mutex_unlock(p->left_fork);
		return (1);
	}
	pthread_mutex_lock(p->right_fork);
	if (print_routine(time_now(p) - p->thread_start, p, FORK))
	{
		pthread_mutex_unlock(p->left_fork);
		pthread_mutex_unlock(p->right_fork);
		return (1);
	}
	if (print_routine(time_now(p) - p->thread_start, p, EAT))
	{
		pthread_mutex_unlock(p->left_fork);
		pthread_mutex_unlock(p->right_fork);
		return (1);
	}
	p->last_meal = time_now(p);
	p->iter_num++;
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
	return (0);
}

void	*thread_routine(void *job)
{
	int		starved;
	t_philo	*philo;

	starved = 0;
	philo = (t_philo *)job;
	if (philo->id & 1)
		usleep(150);
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

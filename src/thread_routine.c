/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:16:12 by mlazzare          #+#    #+#             */
/*   Updated: 2021/11/02 09:41:38 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	unlock_mutex(t_philo *p)
{
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
	return (EXIT_FAILURE);
}

int	someone_died(long int now, t_philo *p)
{
	print_routine(now, p, DIE);
	p->params->over = 1;
	p->dead = 1;
	unlock_mutex(p);
	return (1);
}

int	check_death(t_philo *p)
{
	long int	now;

	now = time_now() - p->last_meal;
	pthread_mutex_lock(p->params->death);
	if (p->dead || now > p->params->time2die)
	{
		pthread_mutex_unlock(p->params->death);
		return (someone_died(now, p));
	}
	pthread_mutex_unlock(p->params->death);
	return (0);
}

int	ft_think(t_philo *p)
{
	long int	now;

	now = time_now();
	print_routine(now - p->last_meal, p, THINK);
	if (!p->params->over && (now - p->last_meal) > p->params->time2die)
		return (someone_died(now - p->last_meal, p));
	return (0);
}

int	ft_sleep(t_philo *p)
{
	long int	now;

	now = time_now();
	while (!p->params->over && (now - p->last_meal) < p->params->time2sleep)
	{
		if (now - p->last_meal > p->params->time2die)
			return (someone_died(now - p->last_meal, p));
		now = time_now();
	}
	p->last_sleep = now;
	print_routine(now - p->last_meal, p, SLEEP);
	return (0);
}

int	ft_eat(t_philo *p)
{
	pthread_mutex_lock(p->left_fork);
	if (print_routine(time_now() - p->last_meal, p, FORK))
	{
		pthread_mutex_unlock(p->left_fork);
		return (1);
	}
	pthread_mutex_lock(p->right_fork);
	if (print_routine(time_now() - p->last_meal, p, FORK))
	{
		unlock_mutex(p);
		return (1);
	}
	if (print_routine(time_now() - p->last_meal, p, EAT))
	{
		unlock_mutex(p);
		return (1);
	}
	p->last_meal = time_now();
	p->params->last_meal = p->last_meal;
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
	if (philo->id & 0)
		ft_usleep(150);
	philo->last_meal = time_now();
	philo->params->last_meal = philo->last_meal;
	while (!philo->dead && !philo->params->over)
	{
		if (!starved)
			starved = ft_eat(philo);
		if (!starved && !philo->dead && !philo->params->over)
			starved = ft_sleep(philo);
		if (!starved && !philo->dead && !philo->params->over)
			starved = ft_think(philo);
		if (starved)
			check_death(philo);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:16:12 by mlazzare          #+#    #+#             */
/*   Updated: 2021/10/31 10:12:19 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int someone_died(long int now, t_philo *p)
{
	pthread_mutex_lock(p->params->death);
	if (p->dead)
	{
		pthread_mutex_unlock(p->params->death);
		return (1);
	}
	printf("[ %ld ms ] Philosopher %d %s\n", now, p->id, DIE);
	p->params->over = 1;
	p->dead = 1;
	pthread_mutex_unlock(p->params->death);
	return (1);
}

int check_death(t_philo *p)
{
	int			died;
	long int	now;

	died = 0;
	pthread_mutex_lock(p->params->death);
	if (p->dead)
	{
		pthread_mutex_unlock(p->params->death);
		return (1);
	}
	now = current_time() - p->last_meal;
	if (now > p->params->time2die)
		died = someone_died(now, p);
	pthread_mutex_unlock(p->params->death);
	return (died);
}

int ft_think(t_philo *p)
{
	long int now;
	
	now = current_time();
	print_routine(now - p->start, p, THINK);
	if (!p->params->over && (now - p->last_meal) > p->params->time2eat)
		return (someone_died(now - p->last_meal, p));
	return (0);
}

int ft_sleep(t_philo *p)
{
	long int now;
	
	now = current_time();
	while (!p->params->over && (now - p->last_meal) < p->params->time2sleep)
	{
		if (now - p->last_meal > p->params->time2die)
			return (someone_died(now - p->last_meal, p));
		now = current_time();   
	}    
	p->last_sleep = now;
	print_routine(now - p->start, p, SLEEP);
	return (0);
}

int unlock_mutex(t_philo *p)
{
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
	return (EXIT_FAILURE);
}

int ft_eat(t_philo *p)
{
	int	fork;

	while (current_time() - p->last_meal < p->params->time2die)
	{
		if (!pthread_mutex_lock(p->left_fork))
		{
			fork = print_routine(current_time() - p->last_meal, p, FORK);
			break ;
		}
	}
	if (fork)
	{
		pthread_mutex_unlock(p->left_fork);
		return (someone_died(current_time() - p->last_meal, p));
	}
	while (current_time() - p->last_meal < p->params->time2die)
	{
		if (!pthread_mutex_lock(p->right_fork))
		{
			fork = print_routine(current_time() - p->last_meal, p, FORK);
			break ;
		}
	}	
	if (fork)
	{
		unlock_mutex(p);
		return (someone_died(current_time() - p->last_meal, p));
	}
	fork = print_routine(current_time() - p->last_meal, p, EAT);
	if (fork)
	{
		unlock_mutex(p);
		return (someone_died(current_time() - p->last_meal, p));
	}
	p->last_meal = current_time();
	p->params->last_meal = p->last_meal;
	p->iter_num++;
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
	return (0);
}

void *thread_routine(void *job)
{
	int		starved;
	t_philo *philo;

	starved = 0;
	philo = (t_philo *)job;
	if (philo->id&1)
		ft_usleep(150);
	philo->start = current_time();
	philo->last_meal = philo->start;
	philo->params->last_meal = philo->last_meal;
	while (!philo->dead && !philo->params->over)
	{
		printf("starved %d\n", starved);
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
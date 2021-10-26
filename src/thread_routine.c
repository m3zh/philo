/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:16:12 by mlazzare          #+#    #+#             */
/*   Updated: 2021/10/26 12:41:10 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void someone_died(long int now, t_philo *p)
{
	printf("[ %ld ms ] Philosopher %d %s\n", now, p->id, DIE);
	p->params->over = 1;
	p->dead = 1;
}

void ft_think(t_philo *p)
{
	long int now;
	
	now = current_time();
	print_routine(now - p->start, p, THINK);
	while (now - p->last_sleep < p->params->time2die)
		now = current_time();
	if (!p->params->over && (now - p->last_meal) > p->params->time2eat)
		return (someone_died(now - p->last_meal, p));
}

void ft_sleep(t_philo *p)
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
}

void ft_eat(t_philo *p)
{
	long int now;

	pthread_mutex_lock(&p->left_fork);
	print_routine(current_time() - p->last_meal, p, FORK);
	if (p->params->num > 1)
		pthread_mutex_lock(&p->right_fork);
	print_routine(current_time() - p->last_meal, p, FORK);
	now = current_time();
	if (now - p->last_meal > p->params->time2die)
		return (someone_died(now - p->last_meal, p));
	while (!p->params->over && (now - p->last_meal) < p->params->time2eat)
	{
		if (now - p->last_meal > p->params->time2die)
			return (someone_died(now - p->last_meal, p));
		now = current_time();   
	}
	p->last_meal = now;
	print_routine(p->last_meal - p->start, p, EAT); 
	p->iter_num++;
	pthread_mutex_unlock(&p->left_fork);
	if (p->params->num > 1)
		pthread_mutex_unlock(&p->right_fork);
}

void *thread_routine(void *job)
{
	t_philo *philo;

	philo = (t_philo *)job;
	if (philo->id&1)
		ft_usleep(5);
	philo->start = current_time();
	philo->last_meal = philo->start;
	while (!philo->dead || !philo->params->over)
	{
		ft_eat(philo);
		if (!philo->dead || !philo->params->over)
			ft_sleep(philo);
		if (!philo->dead || !philo->params->over)
			ft_think(philo);        
	}   
	return (NULL);    
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:16:12 by mlazzare          #+#    #+#             */
/*   Updated: 2021/10/26 11:31:30 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void someone_died(long int now, t_philo *p)
{
	printf("[ %ld ms ] Philosopher %d %s\n", now - p->params->start, p->id, DIE);
	p->params->over = 1;
	p->dead = 1;
}

void ft_think(t_philo *p)
{
	long int now;
	
	now = current_time();
	printf("[ %ld ms ] Philosopher %d %s\n", now - p->time, p->id, THINK);
	while (now - p->time < p->params->time2die)
		now = current_time();   
	if (!p->params->over && now - p->time > p->params->time2eat)
		return (someone_died(now, p));
}

void ft_sleep(t_philo *p)
{
	long int now;
	
	now = current_time();
	printf("[ %ld ms ] Philosopher %d %s\n", now - p->params->start, p->id, SLEEP);
	while (!p->params->over && now - p->time < p->params->time2sleep)
	{
		if (now - p->time > p->params->time2die)
			return (someone_died(now, p));
		now = current_time();   
	}     
}

void ft_eat(t_philo *p)
{
	long int now;

	now = current_time();
	pthread_mutex_lock(&p->left_fork);
	printf("[ %ld ms ] Philosopher %d %s (left)\n", now - p->params->start, p->id, FORK);
	if (p->params->num > 1)
		pthread_mutex_lock(&p->right_fork);
	now = current_time();
	printf("[ %ld ms ] Philosopher %d %s (right)\n", now - p->params->start, p->id, FORK);
	now = current_time();
	if (now - p->last_meal > p->params->time2die)
		return (someone_died(now, p));
	printf("[ %ld ms ] Philosopher %d %s\n", now - p->params->start, p->id, EAT);
	while (!p->params->over && now - p->time < p->params->time2eat)
	{
		if (now - p->time > p->params->time2die)
			return (someone_died(now, p));
		now = current_time();   
	}         
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
	philo->time = current_time();
	while (!philo->dead && !philo->params->over)
	{
		ft_eat(philo);
		if (!philo->dead && !philo->params->over)
			ft_sleep(philo);
		if (!philo->dead && !philo->params->over)
			ft_think(philo);        
	}   
	return (NULL);    
}
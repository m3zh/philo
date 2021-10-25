/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:16:12 by mlazzare          #+#    #+#             */
/*   Updated: 2021/10/25 17:31:36 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void ft_think(t_philo *p)
{
	long int now;
	
	printf("%lu Philospspher %d %s\n", p->time, p->id, THINK);
	now = p->time;
	while (now - p->time < p->params->time2die)
		now = current_time();   
	if (now - p->time > p->params->time2eat)
	{
		printf("%lu Philospspher %d %s\n", p->time, p->id, DIE);
		p->params->over = 1;
		p->dead = 1;
	}
}

void ft_sleep(t_philo *p)
{
	long int now;
	
	printf("%lu Philospspher %d %s\n", p->time, p->id, SLEEP);
	now = p->time;
	while (now - p->time < p->params->time2sleep)
	{
		if (now - p->time > p->params->time2die)
		{
			printf("%lu Philospspher %d %s\n", p->time, p->id, DIE);
			p->params->over = 1;
			p->dead = 1;
			break ;
		}
		now = current_time();   
	}     
}

void ft_eat(t_philo *p)
{
	long int now;
	p->time = current_time();
	pthread_mutex_lock(&p->left_fork);
	pthread_mutex_lock(&p->right_fork);
	printf("%lu Philospspher %d %s\n", p->time, p->id, EAT);
	now = p->time;
	while (now - p->time < p->params->time2eat)
	{
		if (now - p->time > p->params->time2die)
		{
			printf("%lu Philospspher %d %s\n", p->time, p->id, DIE);
			p->params->over = 1;
			p->dead = 1;
			break ;
		}
		now = current_time();   
	}         
	pthread_mutex_unlock(&p->left_fork);
	pthread_mutex_unlock(&p->right_fork);
}

void *thread_routine(void *job)
{
	t_philo *philo;

	philo = (t_philo *)job;
	if (philo->id&1)
		ft_usleep(1);
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
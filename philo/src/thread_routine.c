/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:16:12 by mlazzare          #+#    #+#             */
/*   Updated: 2021/11/12 17:54:12 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	someone_died(t_philo *p)
{
	print_routine(p, DIE);
	p->params->over = 1;
	p->dead = 1;
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
	return (1);
}

int	check_death(t_philo *p)
{
	long int	now;

	pthread_mutex_lock(p->params->death);
	now = time_now(p) - p->last_meal;
	if (now > p->params->time2die)
	{
		pthread_mutex_unlock(p->params->death);
		return (someone_died(p));
	}
	pthread_mutex_unlock(p->params->death);
	return (0);
}

void	ft_sleep_and_think(t_philo *p)
{
	ft_usleep(p->params->time2eat);
	print_routine(p, SLEEP);
	print_routine(p, THINK);
}

void	ft_eat(t_philo *p)
{
	pthread_mutex_lock(p->left_fork);
	print_routine(p, FORK);
	pthread_mutex_lock(p->right_fork);
	print_routine(p, FORK);
	p->last_meal = time_now(p);
	ft_usleep(p->params->time2eat);
	print_routine(p, EAT);
	p->iter_num++;
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
}

void	*thread_routine(void *job)
{
	t_philo	*p;

	p = (t_philo *)job;
	while(!p->params->ready)
		continue ;
	if (p->id & 1)
		ft_usleep(p->params->time2eat * 0.9 + 1);
	while (!p->params->over)
	{
		ft_eat(p);
		ft_sleep_and_think(p);
	}
	return (NULL);
}

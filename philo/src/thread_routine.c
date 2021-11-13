/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:16:12 by mlazzare          #+#    #+#             */
/*   Updated: 2021/11/13 17:55:02 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	someone_died(t_philo *p)
{
	print_routine(p, DIE);
	p->par->over = 1;
	p->dead = 1;
	pthread_mutex_unlock(p->lf);
	pthread_mutex_unlock(p->rf);
	return (1);
}

int	check_death(t_philo *p)
{
	long int	now;

	pthread_mutex_lock(p->par->death);
	now = time_now() - p->meal;
	if (now >= p->par->t2d)
	{
		pthread_mutex_unlock(p->par->death);
		return (someone_died(p));
	}
	pthread_mutex_unlock(p->par->death);
	return (0);
}

void	ft_sleep_and_think(t_philo *p)
{
	ft_usleep(p->par->t2s);
	print_routine(p, SLEEP);
	print_routine(p, THINK);
}

void	ft_eat(t_philo *p)
{
	pthread_mutex_lock(p->lf);
	print_routine(p, FORK);
	pthread_mutex_lock(p->rf);
	print_routine(p, FORK);
	p->meal = time_now();
	ft_usleep(p->par->t2e);
	print_routine(p, EAT);
	p->iter_num++;
	pthread_mutex_unlock(p->lf);
	pthread_mutex_unlock(p->rf);
}

void	*thread_routine(void *job)
{
	t_philo	*p;

	p = (t_philo *)job;
	while (!p->par->ready)
		continue ;
	if (p->id & 1)
		ft_usleep(p->par->t2e * 0.9 + 1);
	while (!p->par->over)
	{
		ft_eat(p);
		ft_sleep_and_think(p);
	}
	return (NULL);
}

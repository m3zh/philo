/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:16:12 by mlazzare          #+#    #+#             */
/*   Updated: 2021/11/11 16:48:47 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	someone_died(t_philo *p, int unlock, int print)
{
	if (unlock)
	{
		pthread_mutex_unlock(p->left_fork);
		pthread_mutex_unlock(p->right_fork);
	}
	if (print)
	{
		print_routine(p, DIE);
		p->params->over = 1;
	}
	return (1);
}

int	check_death(t_philo *p)
{
	long int	now;
	
	pthread_mutex_lock(p->params->death);
	now = time_now(p) - p->last_meal;
	if (now > p->params->time2die * 1000)
	{
		pthread_mutex_unlock(p->params->death);
		return (someone_died(p, 1, 1));
	}
	pthread_mutex_unlock(p->params->death);
	return (0);
}

void ft_sleep_and_think(t_philo *p)
{
	if (p->params->over)
		return ;
	if (print_routine(p, SLEEP))
		return ;
	while (!p->params->over && time_now(p) - p->sleep < p->params->time2sleep * 1000)
		continue ;
	if (print_routine(p, THINK))
		return ;
}

int	ft_eat(t_philo *p)
{
	pthread_mutex_lock(p->left_fork);
	if (print_routine(p, FORK))
		return (pthread_mutex_unlock(p->left_fork) + 1);
	pthread_mutex_lock(p->right_fork);
	if (print_routine(p, FORK))
		return (someone_died(p, 1, 1));
	p->last_meal = time_now(p);
	if (print_routine(p, EAT))
		return (someone_died(p, 1, 1));
	while (!p->params->over && time_now(p) - p->last_meal < p->params->time2eat * 1000)
		continue ;
	p->sleep = time_now(p);
	p->iter_num++;
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
	return (0);
}

void	*thread_routine(void *job)
{
	t_philo	*philo;

	philo = (t_philo *)job;
	while (!philo->params->ready)
		continue ;
	if (philo->id & 1)
		ft_usleep(philo->params->time2eat * 0.5);
	while (!philo->params->over)
	{
		if (ft_eat(philo) == 0)
			ft_sleep_and_think(philo);
	}
	return (NULL);
}

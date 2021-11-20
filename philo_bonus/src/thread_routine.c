/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:16:12 by mlazzare          #+#    #+#             */
/*   Updated: 2021/11/20 11:25:53 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	someone_died(t_philo *p, int unlock, int print)
{
	if (unlock)
	{
		sem_post(p->par->fork);
		sem_post(p->par->fork);
	}
	if (print)
	{
		sem_wait(p->par->death);
		printf("%ldms %d %s\n", time_now() - p->thread_start,
			p->id, DIE);
		sem_post(p->par->death);
	}
	return (1);
}

int	check_death(t_philo *p)
{
	long int	now;

	sem_wait(p->par->death);
	now = time_now() - p->last_meal;
	if (now >= p->par->t2d)
	{
		p->par->over = 1;
		p->dead = 1;
		sem_post(p->par->death);
		return (someone_died(p, 1, 1));
	}
	sem_post(p->par->death);
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
	sem_wait(p->par->fork);
	print_routine(p, FORK);
	sem_wait(p->par->fork);
	print_routine(p, FORK);
	p->last_meal = time_now();
	print_routine(p, EAT);
	ft_usleep(p->par->t2e);
	p->iter_num++;
	sem_post(p->par->fork);
	sem_post(p->par->fork);
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

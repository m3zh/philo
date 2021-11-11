/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosphers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:31:20 by mlazzare          #+#    #+#             */
/*   Updated: 2021/11/11 16:14:22 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	check_meals(t_philo p, int last)
{
	if (p.params->check_meal && last == p.params->num - 1
		&& p.iter_num == p.params->max_iter)
		return (ft_usleep(300));
	return (0);
}

static void	check_thread(t_params *p, t_philo *philo)
{
	int	i;

	while (!p->over)
	{
		i = -1;
		while (++i < p->num)
			if (check_death(&philo[i]) || check_meals(philo[i], i))
				p->over = 1;
	}
	if (p->check_meal)
	{
		ft_usleep(1 * p->num);
		printf("						\n");
		printf("  All philosophers have eaten %d times\n", p->max_iter);
		return (final_print(1));
	}
	final_print(0);
}

static int	init_thread(t_params *p, t_philo *philo)
{
	int	i;

	i = -1;
	
	while (++i < p->num)
	{
		philo[i].right_fork = philo[(i + 1) % p->num].left_fork;
		if (pthread_create(&philo[i].life_tid, NULL,
				&thread_routine, &philo[i]) == -1)
			return (error_msg("Error\nFailed to create thread\n", p, philo, 2));
	}
	i = -1;
	p->start = time_now(philo);
	while (++i < p->num)
	{
		philo[i].thread_start = philo->params->start;
		philo[i].last_meal = philo->params->start;
	}
	p->ready = 1;
	return (0);
}

static void	end_thread(t_params *p, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < p->num)
		pthread_join(philo[i].life_tid, (void *)&philo[i]);
	pthread_mutex_destroy(p->death);
	pthread_mutex_destroy(p->fork);
	pthread_mutex_destroy(p->write);
	free(p->death);
	free(p->fork);
	free(p->write);
	free(philo);
}

int	philosophers(t_params *params)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * params->num);
	if (!philo || init_philo(params, philo))
		return (EXIT_FAILURE);
	if (init_thread(params, philo))
		return (EXIT_FAILURE);
	check_thread(params, philo);
	end_thread(params, philo);
	return (0);
}
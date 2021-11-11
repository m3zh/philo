/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosphers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:31:20 by mlazzare          #+#    #+#             */
/*   Updated: 2021/11/10 14:09:27 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	check_meals(t_philo *p, int last)
{
	return (p->params->check_meal
		&& last == p->params->num - 1
		&& p->iter_num == p->params->max_iter);
}

static void	*check_thread(void *job)
{
	int			i;
	t_params	*p;
	t_philo		*philo;

	p = (t_params *)job;
	philo = (t_philo *)p->philo;
	ft_usleep(5);
	while (!p->over)
	{
		i = -1;
		while (++i < p->num)
			if (check_death(&philo[i]) || check_meals(&philo[i], i))
				p->over = 1;
	}
	if (p->check_meal && philo[p->num - 1].iter_num == p->max_iter)
	{
		ft_usleep(5 * p->num);
		printf("						\n");
		printf("  All philosophers have eaten %d times\n", p->max_iter);
		final_print(1);
		return (NULL);
	}
	final_print(0);
	return (NULL);
}

static int	init_thread(t_params *p, t_philo *philo)
{
	pthread_t	death_tid;
	int			i;

	i = -1;
	p->start = time_now(philo);
	while (++i < p->num)
	{
		if (pthread_create(&philo[i].life_tid, NULL,
				&thread_routine, &philo[i]) == -1)
			return (error_msg("Error\nFailed to create thread\n", p, philo, 2));
	}
	ft_usleep(150);
	if (pthread_create(&death_tid, NULL, &check_thread, p) == -1)
		return (error_msg("Error\nFailed to create death thread\n", p, philo, 2));
	pthread_join(death_tid, NULL);
	return (0);
}

static void	end_thread(t_params *p, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < p->num)
		pthread_detach(philo[i].life_tid);
	ft_usleep(2 * p->num);
	sem_close(p->death);
	sem_unlink("/death");
	sem_close(p->fork);
	sem_unlink("/fork");
	free(philo);
}

int	philosophers(t_params *params)
{
	params->philo = malloc(sizeof(t_philo) * params->num);
	if (!params->philo || init_philo(params, params->philo))
		return (EXIT_FAILURE);
	if (init_thread(params, params->philo))
		return (EXIT_FAILURE);
	end_thread(params, params->philo);
	return (0);
}
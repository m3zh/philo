/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosphers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:31:20 by mlazzare          #+#    #+#             */
/*   Updated: 2021/11/04 20:24:43 by mlazzare         ###   ########.fr       */
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
	int		i;
	int		num;
	t_philo *philo;

	philo = (t_philo *)job;
	num = philo[0].params->num;
	ft_usleep(5);
	while (!philo[0].params->over)
	{
		i = -1;
		while (++i < num)
			if (check_death(&philo[i]) || check_meals(&philo[i], i))
				philo[0].params->over = 1;
		printf("loop\n");
	}
	if (philo[0].params->check_meal && philo[num - 1].iter_num == philo[0].params->max_iter)
	{
		ft_usleep(5 * num);
		printf("						\n");
		printf("  All philosophers have eaten %d times\n", philo[0].params->max_iter);
		final_print(1);
		return (NULL);
	}
	final_print(0);
	return (NULL);
}

static int	init_thread(t_params *p, t_philo *philo)
{
	pthread_t death_tid;
	int	i;

	i = -1;
	p->start = time_now(philo);
	sem_post(p->death);
	while (++i < p->num)
	{
		if (pthread_create(&philo[i].life_tid, NULL,
				&thread_routine, &philo[i]) == -1)
			return (error_msg("Error\nFailed to create thread\n", p, philo, 2));
	}
	if (pthread_create(&death_tid, NULL, &check_thread, philo) == -1)
		return (error_msg("Error\nFailed to create death thread\n", p, philo, 2));
	sem_post(p->death);
	return (0);
}

static void	end_thread(t_params *p, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < p->num)
		pthread_join(philo[i].life_tid, (void *)&philo[i]);
	sem_close(p->death);
	sem_unlink("death");
	sem_close(p->fork);
	sem_unlink("fork");
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
	end_thread(params, philo);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:31:20 by mlazzare          #+#    #+#             */
/*   Updated: 2021/11/11 16:11:14 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_philo(t_params *p, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < p->num)
	{
		philo[i].id = i;
		philo[i].iter_num = 0;
		philo[i].thread_start = 0;
		philo[i].last_meal = 0;
		philo[i].params = p;
		philo[i].left_fork = &p->fork[i];
		philo[i].right_fork = 0;
	}
	return (0);
}

static int	init_params_mutex(t_params *p)
{
	int	i;

	i = -1;
	p->death = 0;
	p->write = 0;
	p->fork = 0;
	p->death = malloc(sizeof(pthread_mutex_t));
	if (!p->death)
		return (error_msg("Error\nMutex death: malloc failed\n", p, 0, 1));
	p->write = malloc(sizeof(pthread_mutex_t));
	if (!p->write)
		return (error_msg("Error\nMutex death: malloc failed\n", p, 0, 1));
	p->fork = malloc(sizeof(pthread_mutex_t) * p->num);
	if (!p->fork)
		return (error_msg("Error\nMutex fork: malloc failed\n", p, 0, 1));
	if (pthread_mutex_init(p->death, NULL) == -1)
		return (error_msg("Error\nMutex death init failed\n", p, 0, 1));
	if (pthread_mutex_init(p->write, NULL) == -1)
		return (error_msg("Error\nMutex write init failed\n", p, 0, 1));
	while (++i < p->num)
		if (pthread_mutex_init(&p->fork[i], NULL) == -1)
			return (error_msg("Error\nMutex init failed\n", p, 0, 1));
	return (0);
}

static int	init_params(t_params *p, char **ag)
{
	int	mutex;

	mutex = 0;
	p->num = ft_atoi(ag[1]);
	if (p->num == 0)
		return (printf("No philo here ...\n"));
	p->ready = 0;
	p->time2die = ft_atoi(ag[2]);
	if (p->time2die == 0)
		return (printf("No time to even be born ...\n"));
	p->time2eat = ft_atoi(ag[3]);
	p->time2sleep = ft_atoi(ag[4]);
	p->max_iter = 0;
	p->check_meal = 0;
	p->start = 0;
	if (ag[5])
	{
		p->check_meal = 1;
		p->max_iter = ft_atoi(ag[5]);
	}
	p->over = 0;
	if (p->num > 0)
		mutex = init_params_mutex(p);
	return (mutex || p->num < 0 || p->time2die < 0 || p->time2eat < 0
		|| p->time2sleep < 0 || p->max_iter < 0);
}

int	main(int ac, char **ag)
{
	t_params	p;

	memset(&p, 0, sizeof(p));
	if ((ac != 5 && ac != 6) || init_params(&p, ag))
		return (error_msg("Error: invalid arguments\n", &p, 0, 1));
	if (philosophers(&p))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

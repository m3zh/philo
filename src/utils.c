/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 15:32:10 by mlazzare          #+#    #+#             */
/*   Updated: 2021/10/30 13:20:03 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int error_msg(char *s, t_philo *p, int malloc)
{
	int	i;

	i = -1;
	if (malloc)
	{
		while (++i < malloc)
			free(p[i].left_fork);
		free(p);
	}		
    return (write(STDERR_FILENO, s, ft_strlen(s)));
}

int print_routine(long int now, t_philo *p, char *action)
{
	printf("dead0\n");
	pthread_mutex_lock(p->params->death);
	if (p->dead)
	{
		printf("dead1\n");
		pthread_mutex_unlock(p->params->death);
		return (1);
	}
    printf("[ %ld ms ] Philosopher %d %s\n", now, p->id, action);
	pthread_mutex_unlock(p->params->death);
	return (0);
}

void stop_simulation(t_philo *p)
{
	printf("All philosophers have eaten %d and are alive\n", p->iter_num);
	p->params->over = 1;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 15:32:10 by mlazzare          #+#    #+#             */
/*   Updated: 2021/11/11 16:44:12 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

int	error_msg(char *s, t_params *par, t_philo *p, int malloc)
{
	int	i;

	i = -1;
	if (malloc)
	{
		if (par->death)
			free(par->death);
		if (par->write)
			free(par->write);
		if (par->fork)
			free(par->fork);
		if (malloc == 2)
			while (++i < par->num)
				free(&p[i]);
	}		
	return (printf("%s", s));
}

int	print_routine(t_philo *p, char *action)
{
	long int	now;

	pthread_mutex_lock(p->params->write);
	if (p->params->over)
		return (pthread_mutex_unlock(p->params->write) + 1);
	now = time_now(p) / 1000 - p->thread_start / 1000;
	printf("[ %ld ms ] %d %s\n", now, p->id, action);
	if (!ft_strcmp(action, DIE))
		p->params->check_meal = 0;
	return (pthread_mutex_unlock(p->params->write));
}

void	final_print(int alive)
{
	printf("						\n");
	if (alive)
		printf("	(☞ﾟヮﾟ)☞ no one died today	\n");
	else
		printf("	¯\\_(ツ)_/¯			\n");
	printf("						\n");
}

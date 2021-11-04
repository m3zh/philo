/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 15:32:10 by mlazzare          #+#    #+#             */
/*   Updated: 2021/11/04 09:34:40 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (((unsigned char*)s1)[i] - ((unsigned char*)s2)[i]);
		i++;
	}
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	error_msg(char *s, t_params *par, t_philo *p, int malloc)
{
	int	i;

	i = -1;
	if (malloc)
	{
		free(par->death);
		free(par->fork);
		if (malloc == 2)
			while (++i < par->num)
				free(&p[i]);
	}		
	return (write(STDERR_FILENO, s, ft_strlen(s)));
}

int	print_routine(long int now, t_philo *p, char *action)
{
	pthread_mutex_lock(p->params->death);
	if (p->dead || p->params->over)
	{
		pthread_mutex_unlock(p->params->death);
		return (1);
	}
	printf("[ %ld ms ] Philosopher %d %s\n", now, p->id, action);
	if (!ft_strcmp(action, DIE))
		p->params->check_meal = 0;
	pthread_mutex_unlock(p->params->death);
	return (0);
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 15:32:10 by mlazzare          #+#    #+#             */
/*   Updated: 2021/11/11 16:51:09 by mlazzare         ###   ########.fr       */
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
		free(par->death);
		free(par->fork);
		if (malloc == 2)
			while (++i < par->num)
				free(&p[i]);
	}		
	return (printf("%s\n", s));
}

int	print_routine(long int now, t_philo *p, char *action)
{
	sem_post(p->params->death);
	if (p->dead || p->params->over)
	{
		sem_wait(p->params->death);
		return (1);
	}
	printf("[ %ld ms ] Philosopher %d %s\n", now, p->id, action);
	if (!ft_strcmp(action, DIE))
		p->params->check_meal = 0;
	sem_wait(p->params->death);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 15:32:10 by mlazzare          #+#    #+#             */
/*   Updated: 2021/11/12 16:22:38 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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

void	print_routine(t_philo *p, char *action)
{
	pthread_mutex_lock(p->params->death);
	if (p->params->over)
	{
		pthread_mutex_unlock(p->params->death);
		return ;
	}
	printf("%ldms %d %s\n", time_now(p) - p->thread_start,
		p->id, action);
	pthread_mutex_unlock(p->params->death);
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 15:32:10 by mlazzare          #+#    #+#             */
/*   Updated: 2021/11/13 18:55:06 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	error_msg(char *s, t_params *par, t_philo *p, int malloc)
{
	if (malloc)
	{
		if (par->death)
			free(par->death);
		if (par->fork)
			free(par->fork);
		if (p)
			free(p);
	}		
	return (printf("%s", s));
}

void	print_routine(t_philo *p, char *action)
{
	pthread_mutex_lock(p->par->death);
	if (p->par->over)
	{
		pthread_mutex_unlock(p->par->death);
		return ;
	}
	printf("%ldms %d %s\n", time_now() - p->thread_start,
		p->id, action);
	pthread_mutex_unlock(p->par->death);
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

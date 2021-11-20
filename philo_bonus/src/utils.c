/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 15:32:10 by mlazzare          #+#    #+#             */
/*   Updated: 2021/11/20 11:27:02 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	error_msg(char *s, t_params *par, t_philo *p, int malloc)
{
	sem_close(par->death);
	sem_unlink("/death");
	sem_close(par->fork);
	sem_unlink("/fork");
	if (malloc)
	{
		if (p)
			free(p);
	}		
	return (printf("%s", s));
}

void	print_routine(t_philo *p, char *action)
{
	sem_wait(p->par->death);
	if (p->par->over)
	{
		sem_post(p->par->death);
		return ;
	}
	printf("%ldms %d %s\n", time_now() - p->thread_start,
		p->id, action);
	sem_post(p->par->death);
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

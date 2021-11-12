/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:34:47 by mlazzare          #+#    #+#             */
/*   Updated: 2021/11/12 17:50:15 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long int	time_now(t_philo *p)
{
	struct timeval	now;

	if (gettimeofday(&now, NULL) == -1)
		error_msg("Gettimeofday failed to get time\n", p->params, 0, 2);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

void	ft_usleep(long int time)
{
	long int	start_time;

	start_time = time_now(0);
	while ((time_now(0) - start_time) < time)
		usleep(time / 10);
}

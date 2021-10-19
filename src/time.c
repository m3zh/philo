/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:34:47 by mlazzare          #+#    #+#             */
/*   Updated: 2021/10/18 15:41:41 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long int		current_time(void)
{
	struct timeval		now;

	if (gettimeofday(&now, NULL) == -1)
		error_msg("Gettimeofday failed to get time\n");
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

void	ft_usleep(long int time)
{
	long int	start_time;

	start_time = current_time();
	while ((current_time() - start_time) < time)
		usleep(time / 10);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 15:32:10 by mlazzare          #+#    #+#             */
/*   Updated: 2021/10/26 17:05:49 by mlazzare         ###   ########.fr       */
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

int error_msg(char *s)
{
    return (write(STDERR_FILENO, s, ft_strlen(s)));
}

void print_routine(long int now, t_philo * p, char *action)
{
    printf("[ %ld ms ] Philosopher %d %s\n", now, p->id, action);
}

void stop_simulation(t_philo *p)
{
	printf("All philosophers have eaten %d and are alive\n", p->iter_num);
	p->params->over = 1;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:31:20 by mlazzare          #+#    #+#             */
/*   Updated: 2021/10/31 10:03:53 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int init_params(t_params *p, char **ag)
{
    int i;

    i = -1;
    p->num = ft_atoi(ag[1]);
    p->forks = p->num;
    p->time2die = ft_atoi(ag[2]);
    p->time2eat = ft_atoi(ag[3]);
    p->time2sleep = ft_atoi(ag[4]);
    p->max_iter = 0;
    if (ag[5])
        p->max_iter = ft_atoi(ag[5]);
    p->iter_num = 0;
    p->over = 0;
    p->last_meal = 0;
    p->death = malloc(sizeof(pthread_mutex_t));
    if (!p->death)
        return (error_msg("Error\nMutex death: malloc failed\n", 0, 0));
    p->fork = malloc(sizeof(pthread_mutex_t) * p->num);
    if (!p->fork)
    {
        free (p->death);
        return (error_msg("Error\nMutex fork: malloc failed\n", 0, 0));
    }
    if (pthread_mutex_init(p->death, NULL) == -1)
        return (error_msg("Error\nMutex init failed\n", 0, 0));
    while (++i < p->num)
        if (pthread_mutex_init(&p->fork[i], NULL) == -1)
            return (error_msg("Error\nMutex init failed\n", 0, 0));
    return (p->num < 0 || p->time2die < 0 || p->time2eat < 0
        || p->time2sleep < 0 || p->max_iter < 0);
}

int main(int ac, char **ag)
{
    static t_params p;
    
    if ((ac != 5 && ac != 6) || init_params(&p, ag))
        return (error_msg("Error: invalid arguments\n", 0, 0));
    if (philosophers(&p))
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}
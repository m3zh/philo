/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:31:20 by mlazzare          #+#    #+#             */
/*   Updated: 2021/10/19 13:21:29 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int init_philo(t_philo *p, char **ag)
{
    p->num = ft_atoi(ag[1]);
    p->forks = p->num;
    p->time2die = ft_atoi(ag[2]);
    p->time2eat = ft_atoi(ag[3]);
    p->time2sleep = ft_atoi(ag[4]);
    p->max_iter = 0;
    if (ag[5])
        p->max_iter = ft_atoi(ag[5]);
    p->philo = malloc(sizeof(t_p) * p->num);
    if (!p->philo)
        return (0);
    p->iter_num = 0;
    p->over = 0;
    return (!(p->num < 0 || p->time2die < 0 || p->time2eat < 0
        || p->time2sleep < 0 || p->max_iter < 0));
}

int main(int ac, char **ag)
{
    t_philo p;
    
    if ((ac != 5 && ac != 6) || !init_philo(&p, ag))
        return (error_msg("Error: invalid arguments\n"));
    if (philosophers(&p))
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}
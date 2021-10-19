/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosphers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:31:20 by mlazzare          #+#    #+#             */
/*   Updated: 2021/10/19 18:26:03 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void hunger_games(t_params *p, t_philo *philo)
{
    (void)philo;
    while (!p->over)
        return ;
}

static int init_thread(t_params *p, t_philo *philo)
{
    int i;
    
    i = -1;
    if (pthread_mutex_init(&p->lock, NULL) == -1)
        return (error_msg("Error\nMutex init failed\n"));
    while(++i < p->num)
    {
        philo[i].id = i;
        philo[i].dead = 0;
        philo[i].iter_num = 0;
        philo[i].eat_time = 0;
        philo[i].params = p;
        if (pthread_create(&philo[i].life_tid, NULL, &thread_routine, &philo[i]) == -1)
            return (error_msg("Error\nFailed to create thread\n"));
    }
    gettimeofday(&p->start, NULL);
    return (0);
}

static void end_thread(t_params *p, t_philo *philo)
{
    int i;
    
    i = -1;
    while (++i < p->num)
        pthread_join(philo[i].life_tid, (void *)&philo[i]);  
    pthread_mutex_destroy(&p->lock);
    free(philo);
}

int philosophers(t_params *params)
{
    int     i;
    t_philo *philo;

    i = -1;
    philo = malloc(sizeof(t_philo) * params->num);
    if (!philo)
        return (0);
    if (init_thread(params, philo) > 0)
        return (EXIT_FAILURE);
    hunger_games(params, philo);
    end_thread(params, philo);
    return (0);
}
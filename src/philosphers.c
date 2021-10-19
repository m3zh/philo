/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosphers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:31:20 by mlazzare          #+#    #+#             */
/*   Updated: 2021/10/19 13:23:09 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void hunger_games(t_philo *p)
{
    while(!p->over)
        return ;
}

static int init_thread(t_philo *p)
{
    int i;

    i = -1;
    if (pthread_mutex_init(&p->lock, NULL) == -1)
        return (error_msg("Error\nMutex init failed\n"));
    while(++i < p->num)
    {
        if (pthread_create(&p->philo[i].life_tid, NULL, &thread_routine, &p->philo[i]) == -1)
            return (error_msg("Error\nFailed to create thread\n"));
    }
    gettimeofday(&p->start, NULL);
    return (0);
}

static void end_thread(t_philo *p)
{
    int i;
    
    i = -1;
    while (++i < p->num)
        pthread_join(p->philo[i].life_tid, (void *)&p->philo[i]);
    pthread_mutex_destroy(&p->lock);
    free(p->philo);
}

int philosophers(t_philo *p)
{
    if (init_thread(p) > 0)
        return (EXIT_FAILURE);
    hunger_games(p);
    end_thread(p);
    return (0);
}
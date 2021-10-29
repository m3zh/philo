/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosphers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:31:20 by mlazzare          #+#    #+#             */
/*   Updated: 2021/10/29 08:10:12 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int init_thread(t_params *p, t_philo *philo)
{
    int i;
    //static pthread_mutex_t *fork;
    
    i = -1;
    p->start = current_time();
    while(++i < p->num)
    {
        philo[i].left_fork = malloc(sizeof(pthread_mutex_t));
        philo[i].id = i;
        philo[i].dead = 0;
        philo[i].iter_num = 0;
        philo[i].last_meal = 0;
        philo[i].last_sleep = 0;
        philo[i].params = p;
        pthread_mutex_init(philo[i].left_fork, NULL);
        philo[i].right_fork = 0;
        if (p->num > 1 && i == p->num - 1)
            philo[i].right_fork = philo[(i + 1) % p->num].left_fork;   
        if (pthread_create(&philo[i].life_tid, NULL, &thread_routine, &philo[i]) == -1)
            return (error_msg("Error\nFailed to create thread\n"));
    }    
    return (0);
}

static void end_thread(t_params *p, t_philo *philo)
{
    int i;
    
    i = -1;
    while (++i < p->num)
        pthread_join(philo[i].life_tid, (void *)&philo[i]);  
    pthread_mutex_destroy(p->death);
    pthread_mutex_destroy(p->fork);
    free(p->death);
    free(p->fork);
    free(philo);
}

int philosophers(t_params *params)
{
    t_philo *philo;

    philo = malloc(sizeof(t_philo) * params->num);
    if (!philo)
        return (0);
    if (init_thread(params, philo))
        return (EXIT_FAILURE);
    end_thread(params, philo);
    return (0);
}
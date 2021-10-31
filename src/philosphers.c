/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosphers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:31:20 by mlazzare          #+#    #+#             */
/*   Updated: 2021/10/31 13:13:05 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void check_thread(t_params *p, t_philo *philo)
{
    int i;

    while (!p->over)
    {
        i = -1;
        while (++i < p->num)
            if (check_death(&philo[i]))
                p->over = 1;
    }
}

static int init_philo(t_params *p, t_philo *philo)
{
    int i;

    i = -1;
    while(++i < p->num)
    {
        philo[i].id = i;
        philo[i].dead = 0;
        philo[i].iter_num = 0;
        philo[i].last_meal = 0;
        philo[i].last_sleep = 0;
        philo[i].params = p;
        philo[i].left_fork = &p->fork[i];
        // if (pthread_mutex_init(philo[i].left_fork, NULL) == -1)
        //     return (error_msg("Error\nLeft fork init failed\n", philo, i));
        philo[i].right_fork = 0;
    }
    return (0);
}

static int init_thread(t_params *p, t_philo *philo)
{
    int i;
    
    i = -1;
    p->start = current_time();
    while(++i < p->num)
    {
        philo[i].right_fork = philo[(i + 1) % p->num].left_fork;
        if (pthread_create(&philo[i].life_tid, NULL, &thread_routine, &philo[i]) == -1)
            return (error_msg("Error\nFailed to create thread\n", p, philo, 2));
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
    if (!philo || init_philo(params, philo))
        return (EXIT_FAILURE);
    if (init_thread(params, philo))
        return (EXIT_FAILURE);
    check_thread(params, philo); 
    end_thread(params, philo);
    return (0);
}
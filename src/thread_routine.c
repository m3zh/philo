/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:16:12 by mlazzare          #+#    #+#             */
/*   Updated: 2021/10/25 15:16:39 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void ft_think(t_philo *p)
{
 long int now;
    
    printf("%lu %d %s\n", p->time, p->id, THINK);
    now = p->time;
    while (now - p->time < p->params->time2think)
        now = current_time(); 
}

void ft_sleep(t_philo *p)
{
    long int now;
    
    printf("%lu %d %s\n", p->time, p->id, SLEEP);
    now = p->time;
    while (now - p->time < p->params->time2sleep)
        now = current_time();  
}

void ft_eat(t_philo *p)
{
    long int now;
    p->time = current_time();
    pthread_mutex_lock(&p->left_fork);
    pthread_mutex_lock(&p->right_fork);
    printf("%lu %d %s\n", p->time, p->id, EAT);
    now = p->time;
    while (now - p->time < p->params->time2eat)
        now = current_time();    
    pthread_mutex_unlock(&p->left_fork);
    pthread_mutex_unlock(&p->right_fork);
}

void *thread_routine(void *job)
{
    t_philo *philo;

    philo = (t_philo *)job;
    if (philo->id&1)
		ft_usleep(10);
    philo->time = current_time();
    while (!philo->dead)
    {
        ft_eat(philo);
        if (!philo->dead)
            ft_sleep(philo);
        if (!philo->dead)
            ft_think(philo);        
    }   
    return (NULL);    
}
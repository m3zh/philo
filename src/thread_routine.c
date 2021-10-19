/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:16:12 by mlazzare          #+#    #+#             */
/*   Updated: 2021/10/19 18:23:37 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void *thread_routine(void *job)
{
    t_philo *philo;

    philo = (t_philo *)job;
    pthread_mutex_lock(&philo->left_fork);
    printf("i'm doing my job, i am no. %ld\n", philo->life_tid);
    pthread_mutex_unlock(&philo->left_fork);
    return (NULL);    
}
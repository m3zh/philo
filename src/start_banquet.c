/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_banquet.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:31:20 by mlazzare          #+#    #+#             */
/*   Updated: 2021/10/17 15:58:25 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void *hunger_games(void *job)
{
    return (job);    
}

int start_banquet(t_philo *p)
{
    int i;
    pthread_t *tid;
    pthread_mutex_t lock;

    i = -1;
    tid = malloc(sizeof(pthread_t) * p->num);
    if (!tid)
        return (error_msg("Error\nMalloc failure in tid creation\n"));
    if (pthread_mutex_init(&lock, NULL) == -1)
        return (error_msg("Error\nMutex init failed\n"));
    while(++i < p->num)
    {
        if (pthread_create(&tid[i], NULL, &hunger_games, NULL) == -1)
            return (error_msg("Error\nFailed to create thread\n"));
    }
    i = -1;
    while (++i < p->num)
        pthread_join(tid[i], NULL);
    pthread_mutex_destroy(&lock);
    free(tid);
    return (0);
}
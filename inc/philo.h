/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:32:05 by mlazzare          #+#    #+#             */
/*   Updated: 2021/10/25 15:09:30 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/time.h>

#define FORK "has taken a fork";
#define EAT "is eating"
#define SLEEP "is sleeping"
#define THINK "is thinking"
#define DIE "died"

typedef struct s_params
{
    int num;
    int forks;
    int time2die;
    int time2eat;
    int time2sleep;
    int max_iter;
    int iter_num;
    int over;
    long int    start;
    pthread_mutex_t lock;
} t_params;

typedef struct s_philo
{
    int id;
    int dead;
    int iter_num;
    long int    eat_time;
    long int    time;
    pthread_t life_tid;
    pthread_t death_tid;
    pthread_mutex_t left_fork;
    pthread_mutex_t right_fork;
    t_params *params;
} t_philo;

int         philosophers(t_params *p);
void        *thread_routine(void *job);
long int    current_time(void);
int		    ft_atoi(const char *str);
void	    ft_usleep(long int time);
int         error_msg(char *s);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:32:05 by mlazzare          #+#    #+#             */
/*   Updated: 2021/10/26 17:05:30 by mlazzare         ###   ########.fr       */
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

#define FORK "has taken a fork"
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
    long int    start;
    long int    last_meal;
    long int    last_sleep;
    pthread_t life_tid;
    pthread_t death_tid;
    pthread_mutex_t left_fork;
    pthread_mutex_t right_fork;
    t_params *params;
} t_philo;

int         philosophers(t_params *p);
void        *thread_routine(void *job);
void        print_routine(long int now, t_philo *p, char *action);
long int    current_time(void);
int		    ft_atoi(const char *str);
void	    ft_usleep(long int time);
void        stop_simulation(t_philo *p);
int         error_msg(char *s);


#endif
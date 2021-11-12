/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:32:05 by mlazzare          #+#    #+#             */
/*   Updated: 2021/11/12 16:19:07 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "\e[0;31mDIED (ভ_ ভ)"
# define LEFT 0
# define RIGHT 1

typedef struct s_params
{
	int				num;
	int				ready;
	int				time2die;
	int				time2eat;
	int				time2sleep;
	int				max_iter;
	int				check_meal;
	int				over;
	long int		start;
	pthread_mutex_t	*death;
	pthread_mutex_t	*fork;
}	t_params;

typedef struct s_philo
{
	int				id;
	int				dead;
	int				iter_num;
	long int		thread_start;
	long int		last_meal;
	pthread_t		life_tid;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_params		*params;
}	t_philo;

int			philosophers(t_params *p);
int			init_philo(t_params *p, t_philo *philo);
int			check_death(t_philo *p);
int			ft_atoi(const char *str);
void		*thread_routine(void *job);
void		ft_usleep(long int	time);
void		final_print(int alive);
void		print_routine(t_philo *p, char *action);
int			error_msg(char *s, t_params *par, t_philo *p, int malloc);
long int	time_now(t_philo *p);

#endif
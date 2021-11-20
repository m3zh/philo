/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:32:05 by mlazzare          #+#    #+#             */
/*   Updated: 2021/11/13 18:38:28 by mlazzare         ###   ########.fr       */
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
# include <sys/stat.h>
# include <fcntl.h>
# include <semaphore.h>

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "\e[0;31mDIED (ভ_ ভ)\e[m"
# define LEFT 0
# define RIGHT 1

typedef struct s_params
{
	int				num;
	int				ready;
	int				t2d;
	int				t2e;
	int				t2s;
	int				max_iter;
	int				check_meal;
	int				over;
	long int		start;
	sem_t			*death;
	sem_t			*fork;
	void			*philo;
}	t_params;

typedef struct s_philo
{
	int				id;
	int				dead;
	int				iter_num;
	long int		thread_start;
	long int		last_meal;
	pthread_t		life_tid;
	t_params		*par;
}	t_philo;

int			philosophers(t_params *p);
int			init_philo(t_params *p, t_philo *philo);
int			check_death(t_philo *p);
int			ft_atoi(const char *str);
int			error_msg(char *s, t_params *par, t_philo *p, int malloc);
int			ft_usleep(long int time);
void		*thread_routine(void *job);
void		final_print(int alive);
void		print_routine(t_philo *p, char *action);
long int	time_now(void);

#endif
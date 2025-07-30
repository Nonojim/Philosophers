/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:29:59 by npederen          #+#    #+#             */
/*   Updated: 2025/04/29 12:29:59 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_rules	t_rules;

typedef struct s_rules
{
	int				nb_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_must_eat;
	long long		start_time;
	int				is_dead;
	int				all_ate;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
}	t_rules;

typedef struct s_philo
{
	int				id;
	int				nb_meals;
	long long		last_meal;
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_rules			*rules;
}	t_philo;

long long	get_time(void);
void		ft_usleep(long long time);
int			ft_atoi(const char *str);
int			init_all(t_rules *rules, t_philo **philos, int argc, char **argv);
void		*routine(void *arg);
void		*monitor(void *arg);

#endif

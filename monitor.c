/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:19:59 by npederen          #+#    #+#             */
/*   Updated: 2025/04/29 13:19:59 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	someone_died(t_rules *rules)
{
	pthread_mutex_lock(&rules->print_mutex);
	if (rules->is_dead)
	{
		pthread_mutex_unlock(&rules->print_mutex);
		return (1);
	}
	pthread_mutex_unlock(&rules->print_mutex);
	return (0);
}

void	*monitor(void *arg)
{
	t_philo		*philos;
	t_rules		*rules;
	int			i;

	philos = (t_philo *)arg;
	rules = philos[0].rules;
	while (1)
	{
		i = 0;
		while (i < rules->nb_philos)
		{
			pthread_mutex_lock(&rules->death_mutex);
			if ((get_time() - philos[i].last_meal) > rules->time_die)
			{
				rules->is_dead = 1;
				pthread_mutex_unlock(&rules->death_mutex);
				pthread_mutex_lock(&rules->print_mutex);
				printf("%lld %d died\n", get_time() - rules->start_time,
					philos[i].id);
				pthread_mutex_unlock(philos->left_fork);
				pthread_mutex_unlock(&rules->print_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&rules->death_mutex);
			i++;
		}
		if (rules->nb_must_eat != -1)
		{
			pthread_mutex_lock(&rules->death_mutex);
			if (rules->all_ate >= rules->nb_philos)
			{
				rules->is_dead = 1;
				pthread_mutex_unlock(&rules->death_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&rules->death_mutex);
		}
		usleep(1000);
	}
	return (NULL);
}

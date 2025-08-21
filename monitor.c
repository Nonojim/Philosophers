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

int	nomorepasta(t_rules *rules)
{
	if (rules->nb_must_eat != -1)
	{
		pthread_mutex_lock(&rules->death_mutex);
		if (rules->all_ate >= rules->nb_philos)
		{
			rules->is_dead = 1;
			pthread_mutex_unlock(&rules->death_mutex);
			return (1);
		}
		pthread_mutex_unlock(&rules->death_mutex);
	}
	return (0);
}

int	deadinplate(t_rules *rules, t_philo *philo)
{
	pthread_mutex_lock(&rules->death_mutex);
	if ((get_time() - philo->last_meal) > rules->time_die)
	{
		rules->is_dead = 1;
		pthread_mutex_unlock(&rules->death_mutex);
		pthread_mutex_lock(&rules->print_mutex);
		if (rules->nb_must_eat == -1 || rules->all_ate < rules->nb_philos)
		{
			printf("%lld %d died\n", get_time() - rules->start_time, philo->id);
			printf("NBR PHILO ALL_ATE%d \n", rules->all_ate);
		}
		pthread_mutex_unlock(&rules->print_mutex);
		return (1);
	}
	pthread_mutex_unlock(&rules->death_mutex);
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
		if (nomorepasta(rules))
			return (NULL);
		i = 0;
		while (i < rules->nb_philos)
		{
			if (nomorepasta(rules))
				break ;
			if (deadinplate(rules, &philos[i]))
				return (NULL);
			i++;
		}
		ft_usleep(2);
	}
	return (NULL);
}

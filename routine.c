/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:29:24 by npederen          #+#    #+#             */
/*   Updated: 2025/04/29 12:29:24 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, char *msg)
{
	long long	time;

	pthread_mutex_lock(&philo->rules->print_mutex);
	pthread_mutex_lock(&philo->rules->death_mutex);
	if (!philo->rules->is_dead)
	{
		time = get_time() - philo->rules->start_time;
		printf("%lld %d %s\n", time, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->rules->print_mutex);
	pthread_mutex_unlock(&philo->rules->death_mutex);
}

void	eat(t_philo *philo)
{
	if (philo->id % 2 == 0) 
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
			
	}
	pthread_mutex_lock(&philo->rules->death_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->rules->death_mutex);
	print_action(philo, "is eating");
	philo->nb_meals++;
	if (philo->rules->nb_must_eat != -1
		&& philo->nb_meals == philo->rules->nb_must_eat)
	{
		pthread_mutex_lock(&philo->rules->death_mutex);
		philo->rules->all_ate++;
		pthread_mutex_unlock(&philo->rules->death_mutex);
	}
	ft_usleep(philo->rules->time_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(10);
		//ft_usleep(philo->rules->time_eat/2);
	while (1)
	{
		if (philo->rules->nb_must_eat != -1 && philo->nb_meals >= philo->rules->nb_must_eat)
			break ;
		pthread_mutex_lock(&philo->rules->death_mutex);
		if (philo->rules->is_dead)
		{
			pthread_mutex_unlock(&philo->rules->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->rules->death_mutex);
		eat(philo);
		print_action(philo, "is sleeping");
		ft_usleep(philo->rules->time_sleep);
		print_action(philo, "is thinking");
	}
	return (NULL);
}

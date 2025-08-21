/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:29:17 by npederen          #+#    #+#             */
/*   Updated: 2025/04/29 12:29:17 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philos)
		if (pthread_mutex_init(&rules->forks[i++], NULL) != 0)
			return (1);
	if (pthread_mutex_init(&rules->print_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&rules->death_mutex, NULL) != 0)
		return (1);
	return (0);
}

int	init_all(t_rules *rules, t_philo **philos, int argc, char **argv)
{
	rules->nb_philos = ft_atoll(argv[1]);
	rules->time_die = ft_atoll(argv[2]);
	rules->time_eat = ft_atoll(argv[3]);
	rules->time_sleep = ft_atoll(argv[4]);
	rules->nb_must_eat = -1;
	if (argc == 6)
		rules->nb_must_eat = ft_atoll(argv[5]);
	rules->is_dead = 0;
	rules->all_ate = 0;
	rules->start_time = get_time();
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->nb_philos);
	if (!rules->forks)
		return (1);
	if (init_mutexes(rules))
		return (1);
	if (init_philos(rules, philos))
		return (1);
	return (0);
}

int	init_philos(t_rules *rules, t_philo **philos)
{
	int	i;

	i = 0;
	*philos = malloc(sizeof(t_philo) * rules->nb_philos);
	if (!*philos)
		return (1);
	while (i < rules->nb_philos)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].nb_meals = 0;
		(*philos)[i].last_meal = get_time();
		(*philos)[i].left_fork = &rules->forks[i];
		(*philos)[i].right_fork = &rules->forks[(i + 1) % rules->nb_philos];
		(*philos)[i].rules = rules;
		i++;
	}
	return (0);
}

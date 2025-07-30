/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:29:08 by npederen          #+#    #+#             */
/*   Updated: 2025/04/29 12:29:08 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc != 5 && argc != 6)
		return (1);
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	cleanup(t_rules *rules, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < rules->nb_philos)
		pthread_mutex_destroy(&rules->forks[i++]);
	pthread_mutex_destroy(&rules->print_mutex);
	pthread_mutex_destroy(&rules->death_mutex);
	free(rules->forks);
	free(philos);
}

int	main(int argc, char **argv)
{
	t_rules		rules;
	t_philo		*philos;
	pthread_t	monitor_thread;
	int			i;

	if (check_args(argc, argv))
		return (printf("Error: invalid arguments\n"), 1);
	if (init_all(&rules, &philos, argc, argv))
		return (printf("Error: init failed\n"), 1);
	i = 0;
	while (i < rules.nb_philos)
	{
		if (pthread_create(&philos[i].thread_id, NULL,
				routine, &philos[i]) != 0)
			return (printf("Error: thread creation failed\n"), 1);
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor, philos) != 0)
		return (printf("Error: monitor thread failed\n"), 1);
	pthread_join(monitor_thread, NULL);
	i = 0;
	while (i < rules.nb_philos)
	{
		pthread_join(philos[i].thread_id, NULL);
		i++;
	}
	cleanup(&rules, philos);
	return (0);
}

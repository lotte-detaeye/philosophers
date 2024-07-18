/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:24:40 by lde-taey          #+#    #+#             */
/*   Updated: 2024/07/18 13:35:10 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*phil_routine(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	while (philo->dinner->philo_dead == 0)
	{
		if (philosopher_takes_forks(philo) == 1)
		{
			philosopher_eats(philo);
			philosopher_puts_forks_down(philo);
		}
		else
			return (0);
		if (!philosopher_sleeps(philo))
			return (0);
		if (!philosopher_thinks(philo))
			return (0);
	}
	return (0);
}

void	start_routine_and_monitoring(t_dinner *din)
{
	size_t		i;
	pthread_t	monitor;

	i = 0;
	din->starting_time = gettime();
	pthread_create(&monitor, NULL, monitoring, (void *)din);
	while (i < din->number)
	{
		pthread_create(&din->philos[i].thread, NULL, 
			phil_routine, (void *)&din->philos[i]);
		i++;
	}
	i = 0;
	while (i < din->number)
	{
		pthread_join(din->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
}

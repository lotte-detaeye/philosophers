/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:14:25 by lde-taey          #+#    #+#             */
/*   Updated: 2024/07/18 12:54:46 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	add_info(t_philo *philo, t_dinner *din, int i)
{
	philo->id = i + 1;
	philo->last_meal = 0;
	philo->is_eating = 0;
	philo->meals_eaten = 0;
	philo->starting_time = 0;
	din->philos[i].left_fork = &din->forks[i];
	if (din->number > 1)
		din->philos[i].right_fork = &din->forks[(i + 1) % din->number];
	else
		din->philos[i].right_fork = NULL;
	philo->dinner = din;
}

static int	init_philosophers_and_forks(t_dinner *din)
{
	size_t	i;

	din->philos = malloc(din->number * sizeof(t_philo));
	if (!din->philos)
		return (0);
	din->forks = malloc((din->number) * sizeof(t_fork));
	if (!din->forks)
	{
		free(din->philos);
		return (0);
	}
	i = 0;
	while (i < din->number)
	{
		din->forks[i].id = i + 1;
		pthread_mutex_init(&din->forks[i].mutex, NULL);
		add_info(&din->philos[i], din, i);
		i++;
	}
	return (1);
}

int	init_dinner(char **argv, t_dinner *din)
{
	din->number = ft_atoi(argv[1]);
	din->time_to_die = ft_atoi(argv[2]);
	din->time_to_eat = ft_atoi(argv[3]);
	din->time_to_sleep = ft_atoi(argv[4]);
	din->philo_dead = 0;
	din->starting_time = gettime();
	din->ready = -1;
	pthread_mutex_init(&din->mutex, NULL);
	pthread_mutex_init(&din->ready_mutex, NULL);
	if (argv[5])
		din->number_of_meals = ft_atoi(argv[5]);
	else
		din->number_of_meals = -1;
	if (!init_philosophers_and_forks(din))
		return (0);
	return (1);
}

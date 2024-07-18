/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:37:29 by lde-taey          #+#    #+#             */
/*   Updated: 2024/07/18 13:27:42 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	checkifeaten(t_dinner *din)
{
	size_t	i;

	if (din->number_of_meals == -1)
		return (0);
	i = 0;
	while (i < din->number)
	{
		if (din->philos[i].meals_eaten < din->number_of_meals)
			return (0);
		i++;
	}
	din->philo_dead = 1;
	return (1);
}

int	checkifdead(t_dinner *dinner)
{
	long long	time;
	size_t		i;

	pthread_mutex_lock(&dinner->mutex);
	time = gettime() - dinner->starting_time;
	pthread_mutex_unlock(&dinner->mutex);
	i = 0;
	while (i < dinner->number)
	{
		if (time - dinner->philos[i].last_meal > dinner->time_to_die)
		{
			if (dinner->philos[i].is_eating == 0)
			{
				dinner->philo_dead = 1;
				printf("%llu Philosopher %zu %s\n", \
					gettime() - dinner->starting_time, \
					dinner->philos[i].id, "died");
				if (dinner->number == 1)
					pthread_mutex_unlock(&dinner->philos[0].left_fork->mutex);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

void	*monitoring(void *dinner)
{
	t_dinner	*din;

	din = (t_dinner *)dinner;
	while (1)
	{
		if (checkifdead(din) == 1 || checkifeaten(din) == 1)
			break ;
	}
	return (0);
}

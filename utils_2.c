/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:29:38 by lde-taey          #+#    #+#             */
/*   Updated: 2024/06/24 13:00:38 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	pick_up_first_fork(t_fork *first_fork, t_philo *philo)
{
	pthread_mutex_lock(&first_fork->mutex);
	if (philo->dinner->philo_dead == 1)
	{
		pthread_mutex_unlock(&first_fork->mutex);
		return (0);
	}
	print_message("has taken a fork", philo);
	return (1);
}

int	pick_up_second_fork(t_fork *first_fork, t_fork *second_fork, t_philo *philo)
{
	pthread_mutex_lock(&second_fork->mutex);
	if (philo->dinner->philo_dead == 1)
	{
		pthread_mutex_unlock(&first_fork->mutex);
		pthread_mutex_unlock(&second_fork->mutex);
		return (0);
	}
	print_message("has taken a fork", philo);
	return (1);
}

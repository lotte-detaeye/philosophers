/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:14:24 by lde-taey          #+#    #+#             */
/*   Updated: 2024/07/18 13:28:10 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// the name of this function is a bit misleading -- when a philosopher
// dies, they cannot put their forks down anymore but in that case it
// is still important to unlock the mutexes
void	philosopher_puts_forks_down(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
}

int	philosopher_sleeps(t_philo *philo)
{
	if (philo->dinner->philo_dead == 0)
	{
		print_message("is sleeping", philo);
		ft_action(philo->dinner->time_to_sleep);
	}
	else
		return (0);
	return (1);
}

int	philosopher_thinks(t_philo *philo)
{
	if (philo->dinner->philo_dead == 0)
		print_message("is thinking", philo);
	else
		return (0);
	return (1);
}

void	philosopher_eats(t_philo *philo)
{
	if (philo->dinner->philo_dead == 1)
	{
		pthread_mutex_unlock(&philo->left_fork->mutex);
		pthread_mutex_unlock(&philo->right_fork->mutex);
		return ;
	}
	philo->is_eating = 1;
	philo->last_meal = gettime() - philo->dinner->starting_time;
	philo->meals_eaten += 1;
	print_message("is eating", philo);
	philo->is_eating = 0;
	ft_action(philo->dinner->time_to_eat);
}

int	philosopher_takes_forks(t_philo *philo)
{
	t_fork	*first_fork;
	t_fork	*second_fork;

	if (philo->dinner->philo_dead == 1)
		return (0);
	if (philo->dinner->number == 1)
	{
		pick_up_first_fork(philo->left_fork, philo);
		return (0);
	}
	if (philo->id % 2 == 0) 
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	if (!pick_up_first_fork(first_fork, philo))
		return (0);
	if (!pick_up_second_fork(first_fork, second_fork, philo))
		return (0);
	return (1);
}

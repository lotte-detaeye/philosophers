/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:43:36 by lde-taey          #+#    #+#             */
/*   Updated: 2024/07/18 12:20:41 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clean_up(t_dinner *dinner)
{
	size_t	i;

	i = 0;
	pthread_mutex_destroy(&dinner->mutex);
	pthread_mutex_destroy(&dinner->ready_mutex);
	while (i < dinner->number)
	{
		pthread_mutex_destroy(&dinner->forks[i].mutex);
		i++;
	}
}

void	free_philos_and_forks(t_dinner *dinner)
{
	free(dinner->philos);
	free(dinner->forks);
}

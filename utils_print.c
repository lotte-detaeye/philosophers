/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:12:01 by lde-taey          #+#    #+#             */
/*   Updated: 2024/07/18 12:29:07 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_message(char *str, t_philo *philo)
{
	long long	timestamp;

	timestamp = gettime() - philo->dinner->starting_time;
	pthread_mutex_lock(&philo->dinner->mutex);
	if (philo->dinner->philo_dead == 0)
	{
		printf("%lld Philosopher %zu %s\n", timestamp, philo->id, str);
		pthread_mutex_unlock(&philo->dinner->mutex);
	}
	else
		pthread_mutex_unlock(&philo->dinner->mutex);
}

void	print_error_message(void)
{
	printf("\nError. Faulty arguments.\n");
	printf("\n");
	printf("To run the program enter:\n");
	printf("\t./philo\n\n");
	printf("Make sure you add the following arguments\n");
	printf("(and check if they are valid)\n");
	printf("\t<number_of_philosophers>\n");
	printf("\t<time_to_die>\n");
	printf("\t<time_to_eat>\n");
	printf("\t<time_to_sleep>\n");
	printf("\tOptional: <number_of_times_each_philosopher_must_eat>\n");
	printf("\nExample 1: ./philo 4 800 200 200\n");
	printf("Example 2: ./philo 4 800 200 200 5\n\n");
	exit (-1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:15:57 by lde-taey          #+#    #+#             */
/*   Updated: 2024/07/18 12:24:16 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_action(size_t duration)
{
	size_t	start;

	start = gettime();
	while (((gettime() - start) < duration))
		usleep(500);
}

// this function returns the number of milliseconds elapsed since 
// the start of the Unix epoch (Jan 1, 1970). It provides a high-
// precision timestamp
long long	gettime(void)
{
	struct timeval	timeofday;

	gettimeofday(&timeofday, NULL);
	return ((timeofday.tv_sec * 1000) + (timeofday.tv_usec / 1000));
}

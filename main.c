/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:15:45 by lde-taey          #+#    #+#             */
/*   Updated: 2024/06/13 11:58:56 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_dinner	dinner;

	if (checkargs(argc, argv))
	{
		init_dinner(argv, &dinner);
		start_routine_and_monitoring(&dinner);
		clean_up(&dinner);
		free_philos_and_forks(&dinner);
	}
	else
		print_error_message();
	return (0);
}

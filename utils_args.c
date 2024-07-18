/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:33:56 by lde-taey          #+#    #+#             */
/*   Updated: 2024/06/14 13:08:03 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int	checknumbers(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	checkargs(int argc, char **argv)
{
	int	i;

	if (!(argc == 5 || argc == 6))
		return (0);
	i = 1;
	while (i < argc)
	{
		if (!checknumbers(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *nptr)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-')
		print_error_message();
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] != '\0' && nptr[i] >= 48 && nptr[i] <= 57)
	{
		result = result * 10 + nptr[i] - 48;
		i++;
	}
	if (result > 2147483647)
		print_error_message();
	return ((int)result);
}

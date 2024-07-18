/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:21:55 by lde-taey          #+#    #+#             */
/*   Updated: 2024/07/18 12:28:18 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_dinner	t_dinner;

typedef struct s_fork 
{
	int				id;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philo
{
	size_t			id;
	pthread_t		thread;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_dinner		*dinner;
	long long		last_meal;
	long long		starting_time;
	size_t			is_eating;
	int				meals_eaten;
	int				dead_flag;
}	t_philo;

typedef struct s_dinner
{
	size_t			number;
	long long		time_to_die;
	size_t			time_to_sleep;
	size_t			time_to_eat;
	int				number_of_meals;
	size_t			starting_time;
	int				philo_dead;
	int				ready;
	pthread_mutex_t	ready_mutex;
	pthread_mutex_t	mutex;
	t_philo			*philos;
	t_fork			*forks;
}	t_dinner;

int			checkargs(int argc, char **argv);
void		print_error_message(void);
int			checknumbers(char *str);
int			ft_isdigit(int c);
int			ft_atoi(const char *nptr);
long long	gettime(void);
int			init_dinner(char **argv, t_dinner *dinner);
void		start_routine_and_monitoring(t_dinner *din);
void		*phil_routine(void *philosopher);
int			philosopher_sleeps(t_philo *philo);
int			philosopher_thinks(t_philo *philo);
void		philosopher_eats(t_philo *philo);
void		philosopher_puts_forks_down(t_philo *philo);
int			philosopher_takes_forks(t_philo *philo);
int			pick_up_first_fork(t_fork *first_fork, t_philo *philo);
int			pick_up_second_fork(t_fork *first_fork, 
				t_fork *second_fork, t_philo *philo);
void		ft_action(size_t duration);
void		print_message(char *str, t_philo *philo);
int			checkifdead(t_dinner *dinner);
int			checkifeaten(t_dinner *din);
void		*monitoring(void *dinner);
void		clean_up(t_dinner *dinner);
void		free_philos_and_forks(t_dinner *dinner);

#endif

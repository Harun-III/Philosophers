/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:31:46 by eghalime          #+#    #+#             */
/*   Updated: 2024/11/03 15:23:54 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_fork_mutexes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philos)
		pthread_mutex_init(&data->forks[i], NULL);
}

/*
** Assigns forks to philosophers in a way that avoids deadlock.
** 
** Even-numbered philosophers pick up their left fork first,
** then their right fork. Odd-numbered philosophers pick up
** their right fork first, then their left fork. This alternating
** order prevents all philosophers from waiting on each other, 
** thereby avoiding deadlock.
*/
void	init_forks(t_data *data)
{
	int		i;
	int		philo_position;
	int		next_fork;
	t_philo	*philos;

	philos = data->philos;
	init_fork_mutexes(data);
	i = -1;
	while (++i < data->nb_philos)
	{
		philo_position = i;
		next_fork = (philo_position + 1) % data->nb_philos;
		if ((philos[i].id % 2) == 0)
		{
			philos[i].left_f = &data->forks[philo_position];
			philos[i].right_f = &data->forks[next_fork];
		}
		else
		{
			philos[i].left_f = &data->forks[next_fork];
			philos[i].right_f = &data->forks[philo_position];
		}
	}
}

void	init_philos(t_data *data)
{
	t_philo	*philos;
	int		i;

	i = -1;
	philos = data->philos;
	while (++i < data->nb_philos)
	{
		philos[i].state = INITIAL;
		philos[i].data = data;
		philos[i].id = i + 1;
		philos[i].nb_meals_had = 0;
		pthread_mutex_init(&philos[i].mut_state, NULL);
		pthread_mutex_init(&philos[i].mut_nb_meals_had, NULL);
		pthread_mutex_init(&philos[i].mut_last_eat_time, NULL);
	}
}

static void	malloc_data(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->nb_philos);
	if (data->philos == NULL)
		error_exit ("Memory allocation error");
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (data->forks == NULL)
	{
		free(data->philos);
		error_exit ("Memory allocation error");
	}
	data->philo_ths = malloc(sizeof(pthread_t) * data->nb_philos);
	if (data->philo_ths == NULL)
	{
		free(data->philos);
		free(data->forks);
		error_exit ("Memory allocation error");
	}
}

/*
** 	- nb_full_p is the number of philosophers that have eaten
**		the maximum number of meals
** 	- keep_iterating is a boolean that is set to false when a
**		philosopher dies or when all philosophers have eaten
**
** Here the data that is not initialzed in the parsing function
** The mutex intialized here are used to protect the data
** that is shared between the threads
*/
void	init_data(t_data *data)
{
	data->nb_full_p = 0;
	data->keep_iterating = true;
	pthread_mutex_init(&data->mut_print, NULL);
	pthread_mutex_init(&data->mut_keep_iter, NULL);
	pthread_mutex_init(&data->mut_start_time, NULL);
	malloc_data(data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:31:46 by eghalime          #+#    #+#             */
/*   Updated: 2024/11/23 23:00:54 by eghalime         ###   ########.fr       */
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

void	init_forks(t_data *data)
{
	int		i;
	t_philo	*philos;

	philos = data->philos;
	init_fork_mutexes(data);
	i = 0;
	philos[0].left_f = &data->forks[0];
	philos[0].right_f = &data->forks[data->nb_philos - 1];
	while (++i < data->nb_philos)
	{
		philos[i].left_f = &data->forks[i];
		philos[i].right_f = &data->forks[i - 1];
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
	data->is_simulation_finished = false;
	pthread_mutex_init(&data->mut_print, NULL);
	pthread_mutex_init(&data->mut_keep_iter, NULL);
	pthread_mutex_init(&data->mut_start_time, NULL);
	pthread_mutex_init(&data->mut_simulation, NULL);
	malloc_data(data);
}

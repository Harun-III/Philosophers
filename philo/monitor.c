/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:32:11 by eghalime          #+#    #+#             */
/*   Updated: 2024/11/23 23:26:00 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_philo_full(t_data *data, t_philo *philo)
{
	bool	result;

	result = false;
	if (get_nb_meals_philo_had(philo) >= data->nb_meals)
		result = true;
	return (result);
}

bool	philo_died(t_philo *philo)
{
	bool	is_dead;

	is_dead = false;
	pthread_mutex_lock(&philo->mut_state);
	pthread_mutex_lock(&philo->mut_last_eat_time);
	if (get_time() - philo->last_eat_time > philo->data->die_time
		&& philo->state != EATING)
	{
		is_dead = true;
		philo->state = DEAD;
	}
	pthread_mutex_unlock(&philo->mut_last_eat_time);
	pthread_mutex_unlock(&philo->mut_state);
	return (is_dead);
}

void	*all_full_routine(void *data_p)
{
	t_data	*data;
	int		i;
	int		nb_philos;

	data = (t_data *)data_p;
	i = -1;
	nb_philos = data->nb_philos;
	while (++i < nb_philos && get_keep_iter(data))
	{
		if (is_philo_full(data, &data->philos[i]) == false)
			i = -1;
	}
	if (get_keep_iter(data) == true)
	{
		set_keep_iterating(data, false);
		notify_all_philos(data);
	}
	return (NULL);
}

static void	philo_died_set_flag(t_data *data, bool *should_continue, int *i)
{
	pthread_mutex_lock(&data->mut_print);
	pthread_mutex_lock(&data->mut_keep_iter);
	if (data->keep_iterating)
	{
		printf("%ld %d %s\n", get_time() - get_start_time(data),
			data->philos[(*i)].id, DIED);
		data->keep_iterating = false;
		notify_all_philos(data);
		*should_continue = false;
	}
	pthread_mutex_unlock(&data->mut_keep_iter);
	pthread_mutex_unlock(&data->mut_print);
}

void	all_alive_routine(t_data *data)
{
	bool	should_continue;
	int		i;

	should_continue = true;
	while (should_continue)
	{
		i = -1;
		while ((++i < data->nb_philos) && should_continue)
		{
			if (philo_died(&data->philos[i]))
				philo_died_set_flag (data, &should_continue, &i);
		}
		usleep(100);
		pthread_mutex_lock(&data->mut_keep_iter);
		should_continue = data->keep_iterating;
		pthread_mutex_unlock(&data->mut_keep_iter);
	}
}

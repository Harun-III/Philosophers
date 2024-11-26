/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:29:37 by eghalime          #+#    #+#             */
/*   Updated: 2024/11/25 23:15:09 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_last_eat_time(t_philo *philo)
{
	long	last_eat_time;

	last_eat_time = philo->last_eat_time;

	return (last_eat_time);
}

bool	get_keep_iter(t_data *data)
{
	bool	keep_iterating;

	pthread_mutex_lock(&data->mut_keep_iter);
	keep_iterating = data->keep_iterating;
	pthread_mutex_unlock(&data->mut_keep_iter);
	return (keep_iterating);
}

t_state	get_philo_state(t_philo *philo)
{
	t_state	state;

	pthread_mutex_lock(&philo->mut_state);
	state = philo->state;
	pthread_mutex_unlock(&philo->mut_state);
	return (state);
}

int	get_nb_meals_philo_had(t_philo *philo)
{
	int	nb_meals_had;
	
	nb_meals_had = philo->nb_meals_had;
	return (nb_meals_had);
}

long	get_start_time(t_data *data)
{
	long	time;

	pthread_mutex_lock(&data->mut_start_time);
	time = data->start_time;
	pthread_mutex_unlock(&data->mut_start_time);
	return (time);
}

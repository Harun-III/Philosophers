/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:29:37 by eghalime          #+#    #+#             */
/*   Updated: 2024/11/26 14:16:52 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_last_eat_time(t_philo *philo)
{
	long	last_eat_time;

	last_eat_time = philo->last_eat_time;
	return (last_eat_time);
}

int	get_nb_meals_philo_had(t_philo *philo)
{
	int	nb_meals_had;

	pthread_mutex_lock(&philo->mut_nb_meals_had);
	nb_meals_had = philo->nb_meals_had;
	pthread_mutex_unlock(&philo->mut_nb_meals_had);
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

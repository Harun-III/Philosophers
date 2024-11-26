/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:32:11 by eghalime          #+#    #+#             */
/*   Updated: 2024/11/26 13:15:09 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_philo_full(t_data *data, t_philo *philo)
{
	bool	result;

	pthread_mutex_lock(&philo->mut_nb_meals_had);
	result = false;
	if (get_nb_meals_philo_had(philo) >= data->nb_meals)
		result = true;
	pthread_mutex_unlock(&philo->mut_nb_meals_had);
	return (result);
}

bool	philo_died(t_philo *philo)
{
	bool		result;
	t_data		*data;
	long		last_meal;
	long		time_of_death;

	data = philo->data;
	result = false;
	pthread_mutex_lock(&philo->mut_last_eat_time);
	last_meal = get_last_eat_time(philo);
	pthread_mutex_unlock(&philo->mut_last_eat_time);
	time_of_death = get_time() - last_meal;
	if (time_of_death > data->die_time)
	{
		pthread_mutex_lock(&data->mut_end_loop);
		philo->data->end_loop = true;
		pthread_mutex_unlock(&data->mut_end_loop);
		pthread_mutex_lock(&data->mut_print);
		printf("%ld %d %s\n", time_of_death, philo->id, DIED);
		result = true;
	}
	return (result);
}

void	*all_full_routine(void *data_p)
{
	t_data	*data;
	int		i;
	int		nb_philos;

	data = (t_data *)data_p;
	i = -1;
	nb_philos = data->nb_philos;
	while (++i < nb_philos)
	{
		if (is_philo_full(data, &data->philos[i]) == false)
			i = -1;
	}
	pthread_mutex_lock(&data->mut_end_loop);
	data->end_loop = true;
	pthread_mutex_unlock(&data->mut_end_loop);
	pthread_mutex_lock(&data->mut_print);
	return (NULL);
}

int	all_alive_routine(t_data *data)
{
	int		i;
	int		nb_philos;
	t_philo	*philos;
	int		end_loop_flag;

	philos = data->philos;
	nb_philos = data->nb_philos;
	i = -1;
	while (++i < nb_philos)
	{
		pthread_mutex_lock(&data->mut_end_loop);
		end_loop_flag = data->end_loop;
		pthread_mutex_unlock(&data->mut_end_loop);
		if (end_loop_flag == 1)
			break ;
		if (philo_died(&philos[i]))
			break ;
		if (i == nb_philos - 1)
			i = -1;
	}
	return (0);
}

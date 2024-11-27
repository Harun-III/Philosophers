/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:32:11 by eghalime          #+#    #+#             */
/*   Updated: 2024/11/27 22:15:01 by eghalime         ###   ########.fr       */
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

static bool	philo_died(t_philo *philos, t_data *data, int i)
{
	bool		result;
	long		last_eat_time;
	long		time_of_death;

	result = false;
	pthread_mutex_lock(&philos[i].mut_last_eat_time);
	last_eat_time = get_last_eat_time(philos);
	pthread_mutex_unlock(&philos[i].mut_last_eat_time);
	time_of_death = get_time() - last_eat_time;
	if (time_of_death > data->die_time)
	{
		pthread_mutex_lock(&data->mut_end_loop);
		data->end_loop = true;
		pthread_mutex_unlock(&data->mut_end_loop);
		pthread_mutex_lock(&data->mut_print);
		printf("%ld %d %s\n", time_of_death, philos->id, DIED);
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
	bool	end_of_loop;

	philos = data->philos;
	nb_philos = data->nb_philos;
	i = -1;
	end_of_loop = false;
	while (1)
	{
		pthread_mutex_lock(&data->mut_end_loop);
		end_of_loop = data->end_loop;
		pthread_mutex_unlock(&data->mut_end_loop);
		if (philo_died(philos, data, i) == true || end_of_loop == true)
		{
			ft_usleep(10);
			return (0);
		}
	}
}

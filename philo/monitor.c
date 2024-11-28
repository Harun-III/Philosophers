/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:32:11 by eghalime          #+#    #+#             */
/*   Updated: 2024/11/28 17:04:23 by eghalime         ###   ########.fr       */
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

static bool	has_philosopher_died(t_philo *philo, t_data *data)
{
	long	last_eat_time;
	long	time_since_last_meal;

	pthread_mutex_lock(&philo->mut_last_eat_time);
	last_eat_time = get_last_eat_time(philo);
	pthread_mutex_unlock(&philo->mut_last_eat_time);
	time_since_last_meal = get_time() - last_eat_time;
	return (time_since_last_meal >= data->die_time);
}

int	all_alive_routine(t_data *data)
{
	int		nb_philos;
	t_philo	*philos;
	int		i;

	(1) && (nb_philos = data->nb_philos, philos = data->philos, i = 0);
	while (1)
	{
		while (i < nb_philos)
		{
			if (get_end_loop_val(data) == true)
				return (0);
			if (has_philosopher_died(&philos[i], data))
			{
				set_end_loop_val(data, true);
				pthread_mutex_lock(&data->mut_print);
				printf("%ld %d %s\n", get_time()
					- get_last_eat_time(&philos[i]), philos[i].id, DIED);
				return (0);
			}
			i++;
		}
		i = 0;
	}
}

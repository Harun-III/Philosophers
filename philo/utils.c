/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:40:13 by eghalime          #+#    #+#             */
/*   Updated: 2024/11/23 23:26:05 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	handle_1_philo(t_philo *philo)
{
	take_left_fork(philo);
	ft_usleep(philo->data->die_time);
	set_philo_state(philo, DEAD);
	return (1);
}

bool	nb_meals_option(t_data *data)
{
	if (data->nb_meals > 0)
		return (true);
	return (false);
}

void	free_data(t_data *data)
{
	int	i;

	set_keep_iterating(data, false);
	i = -1;
	while (++i < data->nb_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].mut_state);
		pthread_mutex_destroy(&data->philos[i].mut_nb_meals_had);
		pthread_mutex_destroy(&data->philos[i].mut_last_eat_time);
	}
	pthread_mutex_destroy(&data->mut_print);
	pthread_mutex_destroy(&data->mut_keep_iter);
	pthread_mutex_destroy(&data->mut_start_time);
	pthread_mutex_destroy(&data->mut_simulation);
	free(data->philo_ths);
	free(data->philos);
	free(data->forks);
}

void	print_msg(t_data *data, int id, char *msg)
{
	long	time;

	time = get_time() - get_start_time(data);
	pthread_mutex_lock(&data->mut_print);
	if (get_keep_iter(data))
		printf("%ld %d %s\n", time, id, msg);
	pthread_mutex_unlock(&data->mut_print);
}

void	notify_all_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		set_philo_state(&data->philos[i], DEAD);
		i++;
	}
}

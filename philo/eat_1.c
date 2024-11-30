/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:28:45 by eghalime          #+#    #+#             */
/*   Updated: 2024/11/30 11:55:23 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_f);
	pthread_mutex_unlock(philo->left_f);
}

void	update_last_meal_time(t_philo *philo)
{
	philo->last_eat_time = get_time();
}

int	philo_sleep(t_data *data, long sleep_time)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < sleep_time)
	{
		if (get_end_loop_val(data) == true)
			return (1);
		usleep(500);
	}
	return (0);
}

int	eat(t_philo *philo)
{
	if (take_forks(philo) == 1)
		return (1);
	print_msg(philo->data, philo->id, EAT);
	pthread_mutex_lock(&philo->mut_nb_meals_had);
	philo->nb_meals_had++;
	pthread_mutex_unlock(&philo->mut_nb_meals_had);
	pthread_mutex_lock(&philo->mut_last_eat_time);
	update_last_meal_time(philo);
	pthread_mutex_unlock(&philo->mut_last_eat_time);
	if (philo_sleep (philo->data, philo->data->eat_time) == 1)
		return (1);
	drop_forks(philo);
	return (0);
}

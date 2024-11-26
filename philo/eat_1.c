/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:28:45 by eghalime          #+#    #+#             */
/*   Updated: 2024/11/26 02:12:54 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_f);
	pthread_mutex_unlock(philo->left_f);
}

void	update_last_meal_time(t_philo *philo)
{
	philo->last_eat_time = get_time();
}

void	update_nb_meals_had(t_philo *philo)
{
	philo->nb_meals_had++;
}

int	eat(t_philo *philo)
{
	take_forks(philo);
	set_philo_state(philo, EATING);
	print_msg(philo->data, philo->id, EAT);

	pthread_mutex_lock(&philo->mut_last_eat_time);
	update_last_meal_time(philo);
	pthread_mutex_unlock(&philo->mut_last_eat_time);

	ft_usleep(philo->data->eat_time);

	pthread_mutex_lock(&philo->mut_nb_meals_had);
	update_nb_meals_had(philo);
	pthread_mutex_unlock(&philo->mut_nb_meals_had);

	drop_forks(philo);

	return (0);
}

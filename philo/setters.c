/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:39:10 by eghalime          #+#    #+#             */
/*   Updated: 2024/11/23 22:40:28 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	set_keep_iterating(t_data *data, bool set_to)
{
	bool	result;

	result = true;
	pthread_mutex_lock(&data->mut_keep_iter);
	data->keep_iterating = set_to;
	pthread_mutex_unlock(&data->mut_keep_iter);
	return (result);
}

void	set_philo_state(t_philo *philo, t_state state)
{
	pthread_mutex_lock(&philo->mut_state);
	if (philo->state != DEAD)
		philo->state = state;
	pthread_mutex_unlock(&philo->mut_state);
}

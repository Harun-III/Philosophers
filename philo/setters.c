/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:39:10 by eghalime          #+#    #+#             */
/*   Updated: 2024/11/27 23:36:18 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_philo_state(t_philo *philo, t_state state)
{
	pthread_mutex_lock(&philo->mut_state);
	philo->state = state;
	pthread_mutex_unlock(&philo->mut_state);
}

void	set_end_loop_val(t_data *data, bool val)
{
	pthread_mutex_lock(&data->mut_end_loop);
	data->end_loop = val;
	pthread_mutex_unlock(&data->mut_end_loop);
}

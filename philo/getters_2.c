/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:30:07 by eghalime          #+#    #+#             */
/*   Updated: 2024/11/02 17:30:09 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_die_time(t_data *data)
{
	return (data->die_time);
}

long	get_sleep_time(t_data *data)
{
	return (data->sleep_time);
}

long	get_eat_time(t_data *data)
{
	return (data->eat_time);
}

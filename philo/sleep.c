/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:39:19 by eghalime          #+#    #+#             */
/*   Updated: 2024/11/28 17:21:40 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_sleep(t_philo *philo)
{
	set_philo_state(philo, SLEEPING);
	print_msg(philo->data, philo->id, SLEEP);
	if (philo_sleep (philo->data, philo->data->sleep_time) == 1)
		return (1);
	return (0);
}

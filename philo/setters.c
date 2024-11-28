/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:39:10 by eghalime          #+#    #+#             */
/*   Updated: 2024/11/28 22:50:33 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_end_loop_val(t_data *data, bool val)
{
	pthread_mutex_lock(&data->mut_end_loop);
	data->end_loop = val;
	pthread_mutex_unlock(&data->mut_end_loop);
}

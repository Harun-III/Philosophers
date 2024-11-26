/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:39:03 by eghalime          #+#    #+#             */
/*   Updated: 2024/11/26 02:13:26 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** This the routine that each philosopher thread will run.
** It will keep running until the philosopher dies.
**
** It will first update the last meal time of the philosopher.
** e.g.
**		Philo 1 last ate at 0ms
** Then it will try to eat, sleep and think in a loop.
**
*/
void	*routine(void *philo_p)
{
	t_philo *philo;
	bool	end_loop_value;

	philo = (t_philo *)philo_p;
	if (philo->id % 2 == 0)
		ft_usleep(40);
	while (true)
	{
		pthread_mutex_lock(&philo->data->mut_end_loop);
		end_loop_value = philo->end_loop;
		pthread_mutex_unlock(&philo->data->mut_end_loop);

		if (end_loop_value == false)
			return (NULL);

		eat(philo);
		ft_sleep(philo);
		think(philo);
	}

	return (NULL);
}

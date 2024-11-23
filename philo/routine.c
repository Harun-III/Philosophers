/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:39:03 by eghalime          #+#    #+#             */
/*   Updated: 2024/11/23 22:57:08 by eghalime         ###   ########.fr       */
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
	t_philo	*philo;
	bool	should_continue;
	bool	simulation_finished;

	should_continue = true;
	philo = (t_philo *)philo_p;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->eat_time - 10);
	while (should_continue)
	{
		pthread_mutex_lock(&philo->data->mut_simulation);
		simulation_finished = philo->data->is_simulation_finished;
		pthread_mutex_unlock(&philo->data->mut_simulation);
		if (simulation_finished || (eat(philo) != 0))
			break ;
		pthread_mutex_lock(&philo->data->mut_keep_iter);
		should_continue = philo->data->keep_iterating;
		pthread_mutex_unlock(&philo->data->mut_keep_iter);
		if (!should_continue || ft_sleep(philo) != 0 || think(philo) != 0)
			break ;
	}
	return (NULL);
}

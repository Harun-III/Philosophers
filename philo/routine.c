/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:39:03 by eghalime          #+#    #+#             */
/*   Updated: 2024/11/28 16:50:19 by eghalime         ###   ########.fr       */
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

	philo = (t_philo *)philo_p;
	if (philo->id % 2 == 0)
		ft_usleep(40);
	while (true)
	{
		if (get_end_loop_val(philo->data))
			break ;
		if (eat(philo) == 1)
			break ;
		if (get_end_loop_val(philo->data))
			break ;
		if (ft_sleep(philo) == 1)
			break ;
		if (get_end_loop_val(philo->data))
			break ;
		think(philo);
		if (get_end_loop_val(philo->data))
			break ;
	}
	return (NULL);
}

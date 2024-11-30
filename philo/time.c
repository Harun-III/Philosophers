/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:39:36 by eghalime          #+#    #+#             */
/*   Updated: 2024/11/30 12:05:46 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** This function id made because usleep() is not precise enough
** and can be off by a few milliseconds.
** Which can cause the philosophers to die.
** let's do and example:
** if we want to sleep for 1000 ms
**		so we pass ft_usleep(1000)
**   	we will get the current time first
**  	start == 1725181908647 // this time since epoch in ms
**   	then we will loop until the difference between the current time
**   	and the start time is 1000ms
**   	so we will keep looping until the current time - start time == 1000
**      we usleep for 500ms because we don't want to keep the CPU busy
**      and since usleep works in microseconds and we want to sleep for 1000ms
**      it wont effect the precision of the sleep
*/
void	ft_usleep(long sleep_time)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < sleep_time)
		usleep(500);
}

/*
** This function returns the current time in milliseconds
** by combining the seconds
** and microseconds components from gettimeofday()
*/
long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * (long)1000) + (tv.tv_usec / (long)1000));
}

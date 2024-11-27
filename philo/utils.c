/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:40:13 by eghalime          #+#    #+#             */
/*   Updated: 2024/11/27 21:12:19 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	handle_1_philo(t_philo *philo)
{
	printf("one philo\n");
	take_left_fork(philo);
	ft_usleep(philo->data->die_time);
	set_philo_state(philo, DEAD);
	return (1);
}

bool	nb_meals_option(t_data *data)
{
	if (data->nb_meals > 0)
		return (true);
	return (false);
}

void	free_data(t_data *data)
{
	int	i;
	int	nb_philos;

	nb_philos = data->nb_philos;
	i = -1;
	pthread_mutex_destroy(&data->mut_print);
	pthread_mutex_destroy(&data->mut_keep_iter);
	pthread_mutex_destroy(&data->mut_start_time);
	pthread_mutex_destroy(&data->mut_end_loop);
	free(data->philo_ths);
	free(data->philos);
	free(data->forks);
	while (++i < nb_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].mut_state);
		pthread_mutex_destroy(&data->philos[i].mut_nb_meals_had);
		pthread_mutex_destroy(&data->philos[i].mut_last_eat_time);
	}
}

void	print_msg(t_data *data, int id, char *msg)
{
	(void)msg;
	long	time;

	time = get_time() - get_start_time(data);
	pthread_mutex_lock(&data->mut_print);
	// fprintf(stdout, "I am thread id %d end of loop is %d\n", id, data->end_loop);
	printf("%ld %d %s\n", time, id, msg);
	pthread_mutex_unlock(&data->mut_print);
}

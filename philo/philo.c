/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:35:26 by eghalime          #+#    #+#             */
/*   Updated: 2024/11/26 12:20:15 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	run_threads(t_data *data)
{
	int	i;
	int	nb_of_philos;

	nb_of_philos = data->nb_philos;
	i = -1;
	data->start_time = get_time();
	while (++i < nb_of_philos)
	{
		pthread_mutex_lock(&data->philos->mut_last_eat_time);
		update_last_meal_time(&data->philos[i]);
		pthread_mutex_unlock(&data->philos->mut_last_eat_time);
		if (pthread_create(&data->philo_ths[i], NULL,
				routine, &data->philos[i]))
			return (1);
		pthread_detach(data->philo_ths[i]);
	}
	all_alive_routine(data);
	// if (nb_meals_option(data) == true
	// 	&& pthread_create(&data->monit_all_full, NULL,
	// 		all_full_routine, data))
		// return (1);
	// usleep(5000);
	return (0);
}

static void	print_exit_error(void)
{
	error_exit("Invalid number of arguments.\n"
		GREEN"Usage: ./philo <number_of_philosophers> "
		"<time_to_die> <time_to_eat> <time_to_sleep> "
		"[number_of_times_each_philosopher_must_eat]"RST);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (5 == argc || 6 == argc)
	{
		parse_and_set_timers(&data, argv);
		init_data(&data);
		init_philos(&data);
		init_forks(&data);
		if (run_threads(&data) != 0)
		{
			free_data(&data);
			error_exit ("Failed to execute threads");
		}
		else 
		{
			free_data(&data);
			return (3);
		}
	}
	else
		print_exit_error();
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:32:11 by eghalime          #+#    #+#             */
/*   Updated: 2024/11/27 21:17:33 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_philo_full(t_data *data, t_philo *philo)
{
	bool	result;

	result = false;
	if (get_nb_meals_philo_had(philo) >= data->nb_meals)
		result = true;
	return (result);
}

static bool	philo_died(t_philo *philos, t_data *data, int i)
{
	bool		result;
	long		last_eat_time;
	long		time_of_death;

	result = false;
	pthread_mutex_lock(&philos[i].mut_last_eat_time);
	last_eat_time = get_last_eat_time(philos);
	pthread_mutex_unlock(&philos[i].mut_last_eat_time);
	time_of_death = get_time() - last_eat_time;
	if (time_of_death > data->die_time)
	{
		pthread_mutex_lock(&data->mut_end_loop);
		data->end_loop = true;
		pthread_mutex_unlock(&data->mut_end_loop);
		pthread_mutex_lock(&data->mut_print);
		printf("%ld %d %s\n", time_of_death, philos->id, DIED);
		result = true;
	}
	return (result);
}

void	*all_full_routine(void *data_p)
{
	t_data	*data;
	int		i;
	int		nb_philos;

	data = (t_data *)data_p;
	i = -1;
	nb_philos = data->nb_philos;
	while (++i < nb_philos)
	{
		if (is_philo_full(data, &data->philos[i]) == false)
			i = -1;
	}
	pthread_mutex_lock(&data->mut_end_loop);
	data->end_loop = true;
	pthread_mutex_unlock(&data->mut_end_loop);
	pthread_mutex_lock(&data->mut_print);
	return (NULL);
}

int	all_alive_routine(t_data *data)
{
	int		i;
	int		nb_philos;
	t_philo	*philos;
	// int		end_loop_flag;

	philos = data->philos;
	nb_philos = data->nb_philos;

	i = -1;



	while (1)
	{

		// fprintf(stdout, "test bofore entering the philo_died() ;; this is random value from the data structure %ld\n", (&philos[1])->data->die_time);

		if (philo_died(philos, data, i) == true) // this means a philos has dies
		{
			ft_usleep(10);
			fprintf(stdout, "This is the all_alive_routine a philo has died an I am braking\n");
			return (0) ;
		}
	}


	// 	pthread_mutex_lock(&data->mut_end_loop);
	// 	data->end_loop = true;
	// 	pthread_mutex_unlock(&data->mut_end_loop);
	// 		fprintf(stdout, "end loop flag is %d\n", data->end_loop);
	// 	return (0);


	// philos = data->philos;
	// nb_philos = data->nb_philos;
	// i = -1;

	// 		fprintf(stdout, "end loop flag is %d\n", data->end_loop);
	// 		// ft_usleep (200);

	// while (1)
	// {
	// 	pthread_mutex_lock(&data->mut_end_loop);
	// 	end_loop_flag = data->end_loop;
	// 	pthread_mutex_unlock(&data->mut_end_loop);
	// 	if (end_loop_flag == 1)
	// 	{
	// 		// fprintf(stdout, "end loop flag has changed %d\n", end_loop_flag);
	// 		// ft_usleep (1);
	// 		break ;
	// 	}
	// 	if (philo_died(&philos[i]))
	// 	{
	// 		// ft_usleep (1);
	// 		break ;
	// 	}
	// }
	// return (0);
}

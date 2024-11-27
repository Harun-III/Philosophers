/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:32:11 by eghalime          #+#    #+#             */
/*   Updated: 2024/11/27 19:44:06 by eghalime         ###   ########.fr       */
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

	// (void)philo;
	// (void)data;

	// fprintf(stdout, "This is a test inside philo_died :: I'm just printing the id from the philo structure (this should be 1) %d\n", philos[i].id);
	// fprintf(stdout, "This is a test inside philo_died :: I'm just printing a random value from the data: %ld\n", data->die_time);

	bool		result;
	long		last_eat_time;
	long		time_of_death;

	// data = philo->data;
	result = false;

	// fprintf(stdout, "Hellooooooooo\n");
	// ft_usleep (1000);
	// fprintf(stdout, "this is the philo_died() my id %d\n", philo->id);
	// fprintf(stdout, "this is the philo_died() am thesting if therr is a problem with the data (pointer) %ld\n", philo->data->die_time);
	
	pthread_mutex_lock(&philos[i].mut_last_eat_time);
	last_eat_time = get_last_eat_time(philos);
	// fprintf(stdout, "This philo_die funciton :: I just go the get_last_eat_time and it is: %ld\n", last_eat_time);
	pthread_mutex_unlock(&philos[i].mut_last_eat_time);
	time_of_death = get_time() - last_eat_time;
	if (time_of_death > data->die_time)
	{
		pthread_mutex_lock(&data->mut_end_loop);
		data->end_loop = true;
		pthread_mutex_unlock(&data->mut_end_loop);
	// fprintf(stdout, "I'm philo id: %d I last ate at: %ld I will kill myself at: %ld\n", philo->id,last_meal,time_of_death);
	// fprintf(stdout, "And now I will sleep for a bit\n");
	// ft_usleep(100);

	// 	pthread_mutex_lock(&data->mut_print);
	// 	printf("%ld %d %s\n", time_of_death, philo->id, DIED);
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

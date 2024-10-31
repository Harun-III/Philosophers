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
		if (pthread_create(&data->philo_ths[i], NULL,
				&routine, &data->philos[i]))
			return (1);
	}
	if (pthread_create(&data->monit_all_alive, NULL,
			&all_alive_routine, data))
		return (1);
	if (nb_meals_option(data) == true
		&& pthread_create(&data->monit_all_full, NULL,
			&all_full_routine, data))
		return (1);
	return (0);
}

int	join_threads(t_data *data)
{
	int	i;
	int	nb_philos;

	// nb_philos = get_nb_philos(data);
	nb_philos = data->nb_philos;
	i = -1;
	if (pthread_join(data->monit_all_alive, NULL))
		return (1);
	if (nb_meals_option(data) == true
		&& pthread_join(data->monit_all_full, NULL))
		return (1);
	while (++i < nb_philos)
	{
		if (pthread_join(data->philo_ths[i], NULL))
			return (1);
	}
	return (0);
}

// int	philosophers(int argc, char **argv)
// {
// 	t_data	data;

// 	if (init_data(&data, argc, argv) != 0)
// 		return (MALLOC_ERROR);
// 	init_philos(&data);
// 	init_forks(&data);
// 	run_threads(&data);
//     // join_threads(&data);
// 	// free_data(&data);
// 	return (0);
// }

void	leaks(void)
{
	system("leaks a.out | sed '/^$/d' | tail -1");
	// system("leaks philo");
}

int main(int argc, char **argv)
{
	atexit(leaks);

    t_data	data;

    if (5 == argc || 6 == argc)
	{
		//mine	
		parse_and_set_timers(&data, argv);
		init_data(&data, argc, argv);
		// all --------- is file above this line
		init_philos(&data);
		init_forks(&data);
		if(run_threads(&data) != 0)
		{
			free_data(&data);
			error_exit ("Failed to execute threads");
		}
		if(join_threads(&data) != 0)
		{
			free_data(&data);
			error_exit ("Failed to join threads");
		}
		free_data(&data);
		// the test
			//print_initial_state(&data);
				
		//	parse_input(&table, argv);
		// time to_die + to_eat + to_sleep + number_of_meals are all set and
		//data_init(&table);

		// testing fucntions
			//print_initial_state(&table);

		// dinner_start(&table);
	//	clean(&table);
	}
	else
	{
        error_exit("Invalid number of arguments.\n"
			GREEN"Usage: ./philo <number_of_philosophers> "
			"<time_to_die> <time_to_eat> <time_to_sleep> "
			"[number_of_times_each_philosopher_must_eat]"RST);
	}
	return (0);
}
// int	main(int argc, char **argv)
// {
// 	if (check_input(argc, argv) != 0)
// 	{
// 		print_instruction();
// 		return (WRONG_INPUT);
// 	}
// 	if (philosophers(argc, argv) != 0)
// 		return (MALLOC_ERROR);
// 	return (0);
// }

// fix printing
// fix philo_died()
// fix routing order MAYBE
// WHAT SHOULD IT DO WHEN NB_MEALS IS <= 0?
// is it possible to print in smaller periods?
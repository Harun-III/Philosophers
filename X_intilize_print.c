#include <stdio.h>
#include "philo.h"

void	print_initial_state(t_data *table)
{
	int		i, j;
	int		philos_per_row = 5;
	t_philo	*philo;

	// Print Table Initialization
	printf(W "Table Initialization:\n" RST);
	printf(W "=====================\n" RST);
	printf(C "Number of Philosophers: " YELLOW "%d\n" RST, table->nb_philos);
	printf(C "Time to Die: " YELLOW "%ld\n" RST, table->die_time);
	printf(C "Time to Eat: " YELLOW "%ld\n" RST, table->eat_time);
	printf(C "Time to Sleep: " YELLOW "%ld\n" RST, table->sleep_time);
	printf(C "Limit of Meals: " YELLOW "%d\n" RST, table->nb_meals);
	// printf(C "Simulation Start Time: " YELLOW "%ld\n" RST, table->start_simulation);
	// printf(C "Simulation Ended: " YELLOW "%s\n" RST, table->end_simulation ? "True" : "False");
	// printf(C "All Threads Ready: " YELLOW "%s\n" RST, table->all_threads_ready ? "True" : "False");
	// printf(C "Threads Running: " YELLOW "%ld\n\n" RST, table->threads_running_nbr);

	// Print Philosophers and Forks
	// printf(W "Philosophers State:\n" RST);
	// printf(W "===================\n" RST);

	// for (i = 0; i < table->philo_nbr; i += philos_per_row)
	// {
	// 	int current_chunk = (table->philo_nbr - i) < philos_per_row ? (table->philo_nbr - i) : philos_per_row;

	// 	// Print Philosopher IDs
	// 	for (j = 0; j < current_chunk; j++)
	// 	{
	// 		philo = &table->philos[i + j];
	// 		printf(GREEN "Philosopher %d:\t\t" RST, philo->id);
	// 	}
	// 	printf("\n");

	// 	// Print Full Status
	// 	for (j = 0; j < current_chunk; j++)
	// 	{
	// 		philo = &table->philos[i + j];
	// 		printf(M "  Full: " YELLOW "%s\t\t" RST, philo->full ? "True" : "False");
	// 	}
	// 	printf("\n");

	// 	// Print Meals Counter
	// 	for (j = 0; j < current_chunk; j++)
	// 	{
	// 		philo = &table->philos[i + j];
	// 		printf(M "  Meals Counter: " YELLOW "%ld\t" RST, philo->meals_counter);
	// 	}
	// 	printf("\n");

	// 	// Print Last Meal Time
	// 	for (j = 0; j < current_chunk; j++)
	// 	{
	// 		philo = &table->philos[i + j];
	// 		printf(M "  Last Meal Time: " YELLOW "%ld\t" RST, philo->last_meal_time);
	// 	}
	// 	printf("\n");

	// 	// Print First Fork ID
	// 	for (j = 0; j < current_chunk; j++)
	// 	{
	// 		philo = &table->philos[i + j];
	// 		printf(M "  First Fork ID: " RED "%d\t" RST, philo->first_fork->fork_id);
	// 	}
	// 	printf("\n");

	// 	// Print Second Fork ID
	// 	for (j = 0; j < current_chunk; j++)
	// 	{
	// 		philo = &table->philos[i + j];
	// 		printf(M "  Second Fork ID: " RED "%d\t" RST, philo->second_fork->fork_id);
	// 	}
	// 	printf("\n");

	// 	// Print Thread ID
	// 	for (j = 0; j < current_chunk; j++)
	// 	{
	// 		philo = &table->philos[i + j];
	// 		printf(M "  Thread ID: " YELLOW "%lu\t\t" RST, philo->thread_id);
	// 	}
	// 	printf("\n\n");
	// }

	// // Print Forks State
	// printf(W "Forks State:\n" RST);
	// printf(W "============\n" RST);

	// for (i = 0; i < table->philo_nbr; i += philos_per_row)
	// {
	// 	int current_chunk = (table->philo_nbr - i) < philos_per_row ? (table->philo_nbr - i) : philos_per_row;

	// 	// Print Fork IDs
	// 	for (j = 0; j < current_chunk; j++)
	// 	{
	// 		printf(BLUE "Fork %d\t\t\t" RST, table->forks[i + j].fork_id);
	// 	}
	// 	printf("\n\n");
	// }
}

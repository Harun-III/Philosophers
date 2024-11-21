/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:37:36 by eghalime          #+#    #+#             */
/*   Updated: 2024/11/21 19:12:30 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>

# define TAKE_FORKS "has taken a fork"
# define THINK "is thinking"
# define SLEEP "is sleeping"
# define EAT "is eating"
# define DIED "died"

/*
** ANSI Escape Sequences for Bold Text Colors
** Usage:
**	printf(R "This is red text." RST);
** Remember to use RST to reset the color after setting it.
*/
# define RST		"\033[0m"	 /* Reset */
# define RED		"\033[1;31m" /* Bold Red */
# define GREEN	"\033[1;32m" /* Bold Green */
# define YELLOW	"\033[1;33m" /* Bold Yellow */
# define BLUE	"\033[1;34m" /* Bold Blue */
# define M		"\033[1;35m" /* Bold Magenta */
# define C		"\033[1;36m" /* Bold Cyan */
# define W		"\033[1;37m" /* Bold White */

typedef enum e_philo_state
{
	EATING = 0,
	SLEEPING = 1,
	THINKING = 2,
	DEAD = 3,
	FULL = 4,
	START = 5
}	t_state;

struct	s_data;

typedef struct s_philo
{
	int				id;
	int				nb_meals_had;
	struct s_data	*data;
	t_state			state;
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
	pthread_mutex_t	mut_state;
	pthread_mutex_t	mut_nb_meals_had;
	pthread_mutex_t	mut_last_eat_time;
	long			last_eat_time;
}	t_philo;

typedef struct s_data
{
	int				nb_philos;
	int				nb_meals;
	int				nb_full_p;
	bool			keep_iterating;
	long			eat_time;
	long			die_time;
	long			sleep_time;
	long			start_time;
	pthread_mutex_t	mut_print;
	pthread_mutex_t	mut_keep_iter;
	pthread_mutex_t	mut_start_time;
	pthread_t		monit_all_alive;
	pthread_t		monit_all_full;
	pthread_t		*philo_ths;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}			t_data;

/* parsing.c */
void		parse_and_set_timers(t_data *data, char **argv);

/* routine.c */
void		*routine(void *philo_p);

/* parse.c */
int			ft_atoi(char *str);

/* init_data.c */
void		init_data(t_data *data);
void		init_philos(t_data *data);
void		init_forks(t_data *data);

/* time.c */
long		get_time(void);
void		ft_usleep(long time);

/* monitoring.c */
void		*all_full_routine(void *data_p);
void		*all_alive_routine(void *data_p);
bool		philo_died(t_philo *philo);

/* eat_1.c */
int			eat(t_philo *philo);
void		update_last_meal_time(t_philo *philo);

// /* eat_2.c */
int			take_forks(t_philo *philo);
int			take_right_fork(t_philo *philo);
int			take_left_fork(t_philo *philo);
void		drop_right_fork(t_philo *philo);
void		drop_left_fork(t_philo *philo);

/* sleep.c */
int			ft_sleep(t_philo *philo);

/* think.c */
int			think(t_philo *philo);

/* getters.c */
bool		get_keep_iter(t_data *data);
long		get_start_time(t_data *data);
t_state		get_philo_state(t_philo *philo);
int			get_nb_meals_philo_had(t_philo *philo);
long		get_last_eat_time(t_philo *philo);

/* setters.c */
void		set_keep_iterating(t_data *data, bool set_to);
void		set_philo_state(t_philo *philo, t_state state);

// /* utils.c */
bool		nb_meals_option(t_data *data);
void		free_data(t_data *data);
void		print_msg(t_data *data, int id, char *msg);
int			handle_1_philo(t_philo *philo);
void		error_exit(const char *message);

#endif

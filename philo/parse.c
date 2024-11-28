/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:34:28 by eghalime          #+#    #+#             */
/*   Updated: 2024/11/28 18:08:20 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static char	*is_string_ok(char *s)
{
	char	*ptr;

	if (s == NULL || s[0] == '\0')
	{
		error_exit("Invalid String");
		return (NULL);
	}
	ptr = s;
	while (*ptr != '\0')
	{
		if (!is_digit(*ptr))
		{
			error_exit("String contains non-digit characters");
			return (NULL);
		}
		ptr++;
	}
	return (s);
}

/*
** This function converts a valid positive integer string to a long integer.
** If the converted value exceeds INT_MAX, the function calls error_exit.
**
** Arguments:
**     s: The input string to be converted to a long integer.
**
** Returns:
**     The converted long integer value.
*/
static long	ft_atol(char *s)
{
	long	return_value;

	return_value = 0;
	if (is_string_ok(s) == NULL)
		return (-1);
	s = is_string_ok(s);
	while (is_digit(*s))
	{
		return_value = (return_value * 10) + (*s - '0');
		if (return_value > INT_MAX)
		{
			error_exit("Value exceeds the maximum limit for an integer");
			return (-1);
		}
		s++;
	}
	return (return_value);
}

static int	check_time(t_data *data)
{
	if (data->die_time < 60 || data->eat_time < 60
		|| data->sleep_time < 60)
	{
		error_exit("Time values must be at least 60 milliseconds");
		return (-1);
	}
	return (0);
}

/*
** example of input:
** 	./philo 5 400 200 200 [5]
** times (i.e. 400, 200, 200)
**	are given in ms
** 	we convert it to microseconds
**	becose of usec
*/
int	parse_and_set_timers(t_data *data, char **argv)
{
	data->nb_philos = ft_atol(argv[1]);
	if (data->nb_philos == 0)
		return (error_exit("Number of philos can't be 0"), -1);
	if (data->nb_philos == -1)
		return (-1);
	data->die_time = ft_atol(argv[2]);
	if (data->die_time == -1)
		return (-1);
	data->eat_time = ft_atol(argv[3]);
	if (data->eat_time == -1)
		return (-1);
	data->sleep_time = ft_atol(argv[4]);
	if (data->sleep_time == -1)
		return (-1);
	if (check_time(data) == -1)
		return (-1);
	if (argv[5])
	{
		data->nb_meals = ft_atol (argv[5]);
		if (data->nb_meals == -1)
			return (-1);
	}
	else
		data->nb_meals = -1;
	return (0);
}

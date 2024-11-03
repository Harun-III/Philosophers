/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:34:28 by eghalime          #+#    #+#             */
/*   Updated: 2024/11/02 17:34:41 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

/*
** This function checks if a given string represents a valid positive integer.
** It skips leading whitespaces, allows an optional '+' sign, and ensures that
** the remaining characters are all digits. If the string contains any invalid
** characters or is empty, the function will call error_exit with an appropriate
** error message.
**
** Arguments:
**     s: The input string to be validated.
**
** Returns:
**     A pointer to the first non-whitespace character after the number if the
**     string is valid. If the string is invalid, the function does not return
**     and terminates the program.
*/
static char	*is_string_ok(char *s)
{
	char	*return_value;

	while (*s)
	{
		while (*s == ' ' || (*s >= 9 && *s <= 13))
			s++;
		if (*s == '-')
			error_exit("Philo does not accept negative values");
		if (*s == '+')
			s++;
		if (!is_digit(*s))
			error_exit("Invalid input: non-digit character encountered");
		return_value = s;
		while (is_digit(*s))
			s++;
		while (*s == ' ' || (*s >= 9 && *s <= 13))
			s++;
		if (*s != '\0')
			error_exit("Invalid input: unexpected characters after number");
	}
	return (return_value);
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
	s = is_string_ok(s);
	while (is_digit(*s))
	{
		return_value = (return_value * 10) + (*s - '0');
		if (return_value > INT_MAX)
			error_exit("Value exceeds the maximum limit for an integer");
		s++;
	}
	return (return_value);
}

void	check_time(t_data *data)
{
	if (data->die_time < 60 || data->eat_time < 60
		|| data->sleep_time < 60)
		error_exit("Time values must be at least 60 milliseconds");
}

/*
** example of input:
** 	./philo 5 400 200 200 [5]
** times (i.e. 400, 200, 200)
**	are given in ms
** 	we convert it to microseconds
**	becose of usec
*/
void	parse_and_set_timers(t_data *data, char **argv)
{
	data->nb_philos = ft_atol(argv[1]);
	data->die_time = ft_atol(argv[2]);
	data->eat_time = ft_atol(argv[3]);
	data->sleep_time = ft_atol(argv[4]);
	check_time(data);
	if (argv[5])
		data->nb_meals = ft_atol (argv[5]);
	else
		data->nb_meals = -1;
}

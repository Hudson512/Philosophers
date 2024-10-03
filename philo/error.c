/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:57:16 by hmateque          #+#    #+#             */
/*   Updated: 2024/10/03 14:52:56 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_stop(char *str)
{
	printf("%s\n", str);
	return (1);
}

long int	get_time_end(struct timeval *start)
{
	struct timeval	end;
	long int		total_time;

	gettimeofday(&end, NULL);
	total_time = (end.tv_sec - start->tv_sec) * 1000 + (end.tv_usec
			- start->tv_usec) / 1000;
	return (total_time);
}

long int	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	add_value(t_philo_info *filo, int value, int i)
{
	if (i == 1)
		filo->num_philo = value;
	else if (i == 2)
		filo->time_to_die = (long int)(value);
	else if (i == 3)
		filo->time_to_eat = (long int)(value * 1e3);
	else if (i == 4)
		filo->time_to_sleep = (long int)(value * 1e3);
	else
		filo->number_of_each = value;
}

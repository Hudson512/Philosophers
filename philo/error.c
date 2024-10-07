/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:57:16 by hmateque          #+#    #+#             */
/*   Updated: 2024/10/07 11:40:34 by hmateque         ###   ########.fr       */
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

void	add_value(t_arg_info *info_args, int value, int i)
{
	if (i == 1)
		info_args->num_philo = value;
	else if (i == 2)
		info_args->time_to_die = (long int)(value);
	else if (i == 3)
		info_args->time_to_eat = (long int)(value * 1e3);
	else if (i == 4)
		info_args->time_to_sleep = (long int)(value * 1e3);
	else
		info_args->number_of_each = value;
}

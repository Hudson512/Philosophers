/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 09:46:42 by hmateque          #+#    #+#             */
/*   Updated: 2024/09/26 12:39:33 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*filosofar(void *arg)
{
	t_filo_param	*param;
	int				id;
	t_philo_info	*filo;

	param = (t_filo_param *)arg;
	id = param->id;
	filo = param->filo;
	while (1)
	{
		printf("%ldms %d is thinking\n", get_time_end(param->start, param->end),id);
		pthread_mutex_lock(&filo->garfos[id]);
		printf("%ldms %d has taken a fork\n", get_time_end(param->start, param->end), id);
		pthread_mutex_lock(&filo->garfos[(id + 1) % filo->num_philo]);
		printf("%ldms %d is eating\n", get_time_end(param->start, param->end), id);
		usleep(filo->time_to_eat);
		pthread_mutex_unlock(&filo->garfos[id]);
		pthread_mutex_unlock(&filo->garfos[(id + 1) % filo->num_philo]);
		printf("%ldms %d is sleeping\n", get_time_end(param->start, param->end), id);
		usleep(filo->time_to_sleep);
	}
	return (NULL);
}

int	ft_init(t_philo_info *filo, struct timeval *start, struct timeval *end)
{
	int				i;
	t_filo_param	*params;

	gettimeofday(start, NULL);
	filo->filosofos = (pthread_t *)malloc(sizeof(pthread_t) * filo->num_philo);
	filo->garfos = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* filo->num_philo);
	filo->ids = (int *)malloc(sizeof(int) * filo->num_philo);
	params = (t_filo_param *)malloc(sizeof(t_filo_param) * filo->num_philo);
	i = -1;
	while (++i < filo->num_philo)
	{
		pthread_mutex_init(&filo->garfos[i], NULL);
		filo->ids[i] = i;
		params[i].filo = filo;
		params[i].id = i;
		params[i].start = start;
		params[i].end = end;
	}
	i = -1;
	while (++i < filo->num_philo)
		pthread_create(&filo->filosofos[i], NULL, filosofar, &params[i]);
	return (0);
}

void	add_value(t_philo_info *filo, int value, int i)
{
	if (i == 1)
		filo->num_philo = value;
	else if (i == 2)
		filo->time_to_die = (long int)(value * 1000);
	else if (i == 3)
		filo->time_to_eat = (long int)(value * 1000);
	else if (i == 4)
		filo->time_to_sleep = (long int)(value * 1000);
	else
		filo->number_of_each = value;
}

long int	get_time_end(struct timeval *start, struct timeval *end)
{
	long int	total_time;

	gettimeofday(end, NULL);
	total_time = (end->tv_sec - start->tv_sec) * 1000 + (end->tv_usec
			- start->tv_usec) / 1000;
	return (total_time);
}

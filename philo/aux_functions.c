/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 09:46:42 by hmateque          #+#    #+#             */
/*   Updated: 2024/09/27 12:19:47 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_filo_param	*param;
	t_philo_info	*filo;
	long			current_time;

	param = (t_filo_param *)arg;
	filo = param->filo;
	while (1)
	{
		current_time = get_current_time();
		printf("\033[0;31m%ld > %ld\033[0m\n", (current_time - param->last_meal_time), filo->time_to_die);
		if ((current_time - param->last_meal_time) > filo->time_to_die)
		{
			filo->flag_de_morte = 1;
			printf("\033[0;31m%ldms %d died\033[0m\n", current_time, param->id);
			return (NULL);
		}
		//printf("\033[0;32m%ldms %d nao morreu\033[0m\n", current_time, param->id);
		usleep(1000);
	}
	return (NULL);
}

void	*filosofar(void *arg)
{
	t_filo_param	*param;
	t_philo_info	*filo;

	param = (t_filo_param *)arg;
	filo = param->filo;
	while (1)
	{
		if (filo->flag_de_morte)
			return (NULL);
		printf("%ldms %d is thinking\n", get_time_end(param->start),
			param->id);
		pthread_mutex_lock(&filo->garfos[param->id]);
		printf("%ldms %d has taken a fork\n", get_time_end(param->start), param->id);
		pthread_mutex_lock(&filo->garfos[(param->id + 1) % filo->num_philo]);
		printf("%ldms %d is eating\n", get_time_end(param->start),
			param->id);
		param->last_meal_time = get_current_time();
		usleep(filo->time_to_eat);
		pthread_mutex_unlock(&filo->garfos[param->id]);
		pthread_mutex_unlock(&filo->garfos[(param->id + 1) % filo->num_philo]);
		if (filo->flag_de_morte)
			return (NULL);
		printf("%ldms %d is sleeping\n", get_time_end(param->start),
			param->id);
		usleep(filo->time_to_sleep);
	}
	return (NULL);
}

int	ft_init(t_philo_info *filo, struct timeval *start)
{
	int				i;
	t_filo_param	*params;

	gettimeofday(start, NULL);
	filo->filosofos = (pthread_t *)malloc(sizeof(pthread_t) * filo->num_philo);
	filo->garfos = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* filo->num_philo);
	filo->ids = (int *)malloc(sizeof(int) * filo->num_philo);
	params = (t_filo_param *)malloc(sizeof(t_filo_param) * filo->num_philo);
	filo->flag_de_morte = 0;
	i = -1;
	while (++i < filo->num_philo)
	{
		pthread_mutex_init(&filo->garfos[i], NULL);
		filo->ids[i] = i;
		params[i].filo = filo;
		params[i].id = i;
		params[i].last_meal_time = get_current_time();
		params[i].start = start;
	}
	i = -1;
	while (++i < filo->num_philo)
	{
		pthread_create(&filo->filosofos[i], NULL, filosofar, &params[i]);
		pthread_create(&filo->filosofos[i], NULL, monitor, &params[i]);
	}
	return (0);
}

void	add_value(t_philo_info *filo, int value, int i)
{
	if (i == 1)
		filo->num_philo = value;
	else if (i == 2)
		filo->time_to_die = (long int)(value);
	else if (i == 3)
		filo->time_to_eat = (long int)(value * 1000);
	else if (i == 4)
		filo->time_to_sleep = (long int)(value * 1000);
	else
		filo->number_of_each = value;
}

long int	get_time_end(struct timeval *start)
{
	struct timeval	end;
	long int		total_time;

	gettimeofday(&end, NULL);  // Obtém o tempo atual diretamente
	total_time = (end.tv_sec - start->tv_sec) * 1000 
				+ (end.tv_usec - start->tv_usec) / 1000;  // Diferença em milissegundos
	return (total_time);
}

long int	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

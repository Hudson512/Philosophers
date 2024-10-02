/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 09:46:42 by hmateque          #+#    #+#             */
/*   Updated: 2024/10/02 12:23:10 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_philo_info	*filo;
	int				i;
	long int		current_time;
	long int		time_since_last_meal;

	filo = (t_philo_info *)arg;
	while (1)
	{
		i = -1;
		while (++i < filo->num_philo)
		{
			current_time = get_current_time();
			time_since_last_meal = (current_time - filo->last_meal_time[i] - filo->time_to_die);
			(void)time_since_last_meal;
			if ((current_time - filo->last_meal_time[i]) > filo->time_to_die)
			{
				filo->flag_de_morte = 1;
				printf("\033[0;31m%ldms %d died\033[0m\n", (get_current_time()
						- filo->start), (i + 1));
				//printf("O filósofo %d morreu após %ldms.\n", (i + 1),time_since_last_meal);
				return (NULL);
			}
		}
		usleep(1000);
	}
	return (NULL);
}

void	*filosofar_1(void *arg)
{
	t_filo_param	*param;
	t_philo_info	*filo;

	param = (t_filo_param *)arg;
	filo = param->filo;
	while (1)
	{
		pthread_mutex_lock(&filo->garfos[param->id]);
		if (print_status("has taken a fork", param->id, filo))
			return (NULL);
		check_num_philo(filo, param->id);
		pthread_mutex_lock(&filo->garfos[(param->id + 1) % filo->num_philo]);
		if (print_status_eating("is eating", param->id, filo))
			return (NULL);
		filo->last_meal_time[param->id] = get_current_time();
		usleep(filo->time_to_eat);
		pthread_mutex_unlock(&filo->garfos[param->id]);
		pthread_mutex_unlock(&filo->garfos[(param->id + 1) % filo->num_philo]);
		if (print_status("is sleeping", param->id, filo))
			return (NULL);
		usleep(filo->time_to_sleep);
		if (print_status("is thinking", param->id, filo))
			return (NULL);
	}
	return (NULL);
}

void	*filosofar_2(void *arg)
{
	t_filo_param	*param;
	t_philo_info	*filo;

	param = (t_filo_param *)arg;
	filo = param->filo;
	while (filo->arr_number_each[param->id])
	{
		pthread_mutex_lock(&filo->garfos[param->id]);
		if (print_status("has taken a fork", param->id, filo))
			return (NULL);
		check_num_philo(filo, param->id);
		pthread_mutex_lock(&filo->garfos[(param->id + 1) % filo->num_philo]);
		if (print_status_eating("is eating", param->id, filo))
			return (NULL);
		filo->last_meal_time[param->id] = get_current_time();
		filo->arr_number_each[param->id]--;
		usleep(filo->time_to_eat);
		pthread_mutex_unlock(&filo->garfos[param->id]);
		pthread_mutex_unlock(&filo->garfos[(param->id + 1) % filo->num_philo]);
		if (print_status("is sleeping", param->id, filo))
			return (NULL);
		usleep(filo->time_to_sleep);
		if (print_status("is thinking", param->id, filo))
			return (NULL);
	}
	return (NULL);
}

int	ft_init(t_philo_info *filo)
{
	int				i;
	t_filo_param	*params;

	filo->filosofos = (pthread_t *)malloc(sizeof(pthread_t) * filo->num_philo);
	filo->garfos = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* filo->num_philo);
	filo->arr_number_each = (int *)malloc(sizeof(int) * filo->num_philo);
	filo->last_meal_time = (long int *)malloc(sizeof(long int)
			* filo->num_philo);
	params = (t_filo_param *)malloc(sizeof(t_filo_param) * filo->num_philo);
	filo->flag_de_morte = 0;
	filo->start = get_current_time();
	i = -1;
	while (++i < filo->num_philo)
	{
		filo->arr_number_each[i] = filo->number_of_each;
		pthread_mutex_init(&filo->garfos[i], NULL);
	}
	i = -1;
	//print_datas(filo);
	while (++i < filo->num_philo)
	{
		params[i].id = i;
		params[i].filo = filo;
		filo->last_meal_time[i] = get_current_time();
		if (filo->number_of_each == 0)
			pthread_create(&filo->filosofos[i], NULL, filosofar_1, &params[i]);
		else
			pthread_create(&filo->filosofos[i], NULL, filosofar_2, &params[i]);
		usleep(filo->num_philo * 100);
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
		filo->time_to_eat = (long int)(value * 1e3);
	else if (i == 4)
		filo->time_to_sleep = (long int)(value * 1e3);
	else
		filo->number_of_each = value;
}

long int	get_time_end(struct timeval *start)
{
	struct timeval	end;
	long int		total_time;

	gettimeofday(&end, NULL);
	// Obtém o tempo atual diretamente
	total_time = (end.tv_sec - start->tv_sec) * 1000 + (end.tv_usec
			- start->tv_usec) / 1000; // Diferença em milissegundos
	return (total_time);
}

long int	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

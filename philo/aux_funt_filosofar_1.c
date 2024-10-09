/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_funt_filosofar_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:59:50 by hmateque          #+#    #+#             */
/*   Updated: 2024/10/09 11:05:27 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philo_info *filo, int first_fork, int second_fork)
{
	if (filo->id > second_fork)
	{
		first_fork = second_fork;
		second_fork = filo->id;
	}
	pthread_mutex_lock(&filo->info->garfos[first_fork]);
	if (print_status("has taken a fork", filo->id, filo))
	{
		pthread_mutex_unlock(&filo->info->garfos[first_fork]);
		return (1);
	}
	check_num_philo(filo, filo->id);
	pthread_mutex_lock(&filo->info->garfos[second_fork]);
	if (print_status("has taken a fork", filo->id, filo))
	{
		if (filo->info->num_philo != 1)
			pthread_mutex_unlock(&filo->info->garfos[first_fork]);
		pthread_mutex_unlock(&filo->info->garfos[second_fork]);
		return (1);
	}
	return (0);
}

int	eat(t_philo_info *filo)
{
	if (print_status_eating("is eating", filo->id, filo))
	{
		pthread_mutex_unlock(&filo->info->garfos[filo->id]);
		if (filo->info->num_philo != 1)
			pthread_mutex_unlock(&filo->info->garfos[(filo->id + 1)
				% filo->info->num_philo]);
		return (1);
	}
	pthread_mutex_lock(&filo->info->death_mutex);
	filo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&filo->info->death_mutex);
	usleep(filo->info->time_to_eat);
	pthread_mutex_unlock(&filo->info->garfos[filo->id]);
	pthread_mutex_unlock(&filo->info->garfos[(filo->id + 1)
		% filo->info->num_philo]);
	return (0);
}

int	sleep_and_think(t_philo_info *filo)
{
	if (print_status("is sleeping", filo->id, filo))
		return (1);
	usleep(filo->info->time_to_sleep);
	if (print_status("is thinking", filo->id, filo))
		return (1);
	return (0);
}

int	eat_2(t_philo_info *filo)
{
	if (print_status_eating("is eating", filo->id, filo))
	{
		pthread_mutex_unlock(&filo->info->garfos[filo->id]);
		if (filo->info->num_philo != 1)
			pthread_mutex_unlock(&filo->info->garfos[(filo->id + 1)
				% filo->info->num_philo]);
		return (1);
	}
	pthread_mutex_lock(&filo->info->death_mutex);
	filo->last_meal_time = get_current_time();
	filo->number_each--;
	pthread_mutex_unlock(&filo->info->death_mutex);
	usleep(filo->info->time_to_eat);
	pthread_mutex_unlock(&filo->info->garfos[filo->id]);
	pthread_mutex_unlock(&filo->info->garfos[(filo->id + 1)
		% filo->info->num_philo]);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 09:46:42 by hmateque          #+#    #+#             */
/*   Updated: 2024/10/08 11:09:01 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_philo_info	*filo;
	int				i;
	long int		current_time;

	filo = (t_philo_info *)arg;
	while (1)
	{
		i = -1;
		while (++i < filo->info->num_philo)
		{
			if (check_all_philo(filo))
				return (NULL);
			pthread_mutex_lock(&filo->info->death_mutex);
			if (filo[i].philo_state == 1)
			{
				current_time = get_current_time();
				if ((current_time
						- filo[i].last_meal_time) > filo->info->time_to_die)
				{
					filo->info->flag_de_morte = 1;
					printf("\033[0;31m%ldms %d died\033[0m\n", (current_time
							- filo->info->start), (i + 1));
					pthread_mutex_unlock(&filo->info->death_mutex);
					return (NULL);
				}
			}
			pthread_mutex_unlock(&filo->info->death_mutex);
		}
		usleep(1000);
	}
	return (NULL);
}

void	*filosofar_1(void *arg)
{
	t_philo_info	*filo;

	filo = (t_philo_info *)arg;
	while (1)
	{
		if ((filo->id > ((filo->id + 1) % filo->info->num_philo)))
		{
			pthread_mutex_lock(&filo->info->garfos[filo->id]);
			if (print_status("has taken a fork", filo->id, filo))
			{
				pthread_mutex_unlock(&filo->info->garfos[filo->id]);
				return (NULL);
			}
			check_num_philo(filo, filo->id);
			pthread_mutex_lock(&filo->info->garfos[(filo->id + 1) % filo->info->num_philo]);
		}
		else
		{
			pthread_mutex_lock(&filo->info->garfos[(filo->id + 1) % filo->info->num_philo]);
			if (print_status("has taken a fork", filo->id, filo))
			{
				pthread_mutex_unlock(&filo->info->garfos[(filo->id + 1) % filo->info->num_philo]);
				return (NULL);
			}
			check_num_philo(filo, filo->id);
			pthread_mutex_lock(&filo->info->garfos[filo->id]);
		}

		if (print_status_eating("is eating", filo->id, filo))
		{
			pthread_mutex_unlock(&filo->info->garfos[filo->id]);
			pthread_mutex_unlock(&filo->info->garfos[(filo->id + 1) % filo->info->num_philo]);
			return (NULL);
		}

		pthread_mutex_lock(&filo->info->death_mutex);
		filo->last_meal_time = get_current_time();
		pthread_mutex_unlock(&filo->info->death_mutex);

		usleep(filo->info->time_to_eat);
		pthread_mutex_unlock(&filo->info->garfos[filo->id]);
		pthread_mutex_unlock(&filo->info->garfos[(filo->id + 1) % filo->info->num_philo]);

		if (print_status("is sleeping", filo->id, filo))
			return (NULL);
		usleep(filo->info->time_to_sleep);

		if (print_status("is thinking", filo->id, filo))
			return (NULL);
	}
	return (NULL);
}


void	*filosofar_2(void *arg)
{
	t_philo_info	*filo;

	filo = (t_philo_info *)arg;
	while (filo->number_each)
	{
		if ((filo->id > ((filo->id + 1) % filo->info->num_philo)))
		{
			pthread_mutex_lock(&filo->info->garfos[filo->id]);
			if (print_status("has taken a fork", filo->id, filo))
			{
				pthread_mutex_unlock(&filo->info->garfos[filo->id]);
				return (NULL);
			}
			check_num_philo(filo, filo->id);
			pthread_mutex_lock(&filo->info->garfos[(filo->id + 1) % filo->info->num_philo]);
		}
		else
		{
			pthread_mutex_lock(&filo->info->garfos[(filo->id + 1) % filo->info->num_philo]);
			if (print_status("has taken a fork", filo->id, filo))
			{
				pthread_mutex_unlock(&filo->info->garfos[(filo->id + 1) % filo->info->num_philo]);
				return (NULL);
			}
			check_num_philo(filo, filo->id);
			pthread_mutex_lock(&filo->info->garfos[filo->id]);
		}

		if (print_status_eating("is eating", filo->id, filo))
		{
			pthread_mutex_unlock(&filo->info->garfos[filo->id]);
			pthread_mutex_unlock(&filo->info->garfos[(filo->id + 1) % filo->info->num_philo]);
			return (NULL);
		}

		pthread_mutex_lock(&filo->info->death_mutex);
		filo->last_meal_time = get_current_time();
		filo->number_each--;
		pthread_mutex_unlock(&filo->info->death_mutex);

		usleep(filo->info->time_to_eat);
		pthread_mutex_unlock(&filo->info->garfos[filo->id]);
		pthread_mutex_unlock(&filo->info->garfos[(filo->id + 1) % filo->info->num_philo]);

		if (print_status("is sleeping", filo->id, filo))
			return (NULL);
		usleep(filo->info->time_to_sleep);

		if (print_status("is thinking", filo->id, filo))
			return (NULL);
	}
	pthread_mutex_lock(&filo->info->death_mutex);
	filo->philo_state = 0;
	pthread_mutex_unlock(&filo->info->death_mutex);
	return (NULL);
}

int	ft_init(t_philo_info *filo, t_arg_info *info_args)
{
	int	i;

	i = -1;
	info_args->garfos = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* info_args->num_philo);
	while (++i < info_args->num_philo)
		pthread_mutex_init(&info_args->garfos[i], NULL);
	pthread_mutex_init(&info_args->death_mutex, NULL);
	i = -1;
	while (++i < info_args->num_philo)
	{
		filo[i].last_meal_time = get_current_time();
		if (info_args->number_of_each == 0)
			pthread_create(&filo[i].filosofos, NULL, filosofar_1, &filo[i]);
		else
			pthread_create(&filo[i].filosofos, NULL, filosofar_2, &filo[i]);
		usleep(info_args->num_philo * 100);
	}
	return (0);
}

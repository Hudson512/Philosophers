/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 09:46:42 by hmateque          #+#    #+#             */
/*   Updated: 2024/09/25 14:47:05 by hmateque         ###   ########.fr       */
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
		printf("Filósofo %d está pensando...\n", id);
		pthread_mutex_lock(&filo->garfos[id]);
		printf("Filósofo %d pegou um garfo...\n", id);
		pthread_mutex_lock(&filo->garfos[(id + 1) % filo->num_philo]);
		printf("Filósofo %d está comendo...\n", id);
		usleep(filo->time_to_eat * 1000);
		pthread_mutex_unlock(&filo->garfos[id]);
		pthread_mutex_unlock(&filo->garfos[(id + 1) % filo->num_philo]);
		printf("Filósofo %d está dormir...\n", id);
		usleep(filo->time_to_die * 1000);
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
	filo->ids = (int *)malloc(sizeof(int) * filo->num_philo);
	params = (t_filo_param *)malloc(sizeof(t_filo_param) * filo->num_philo);
	i = -1;
	while (++i < filo->num_philo)
	{
		pthread_mutex_init(&filo->garfos[i], NULL);
		filo->ids[i] = i;
		params[i].filo = filo;
		params[i].id = i;
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
		filo->time_to_die = value;
	else if (i == 3)
		filo->time_to_eat = value;
	else if (i == 4)
		filo->time_to_sleep = value;
	else
		filo->number_of_each = value;
}

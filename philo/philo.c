/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 08:16:48 by hmateque          #+#    #+#             */
/*   Updated: 2024/10/03 14:49:08 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	int				i;
	t_philo_info	filo;
	pthread_t		monitor_thread;

	if (ac == 5 || ac == 6)
	{
		if ((checker_of_arguments(ac, av, &filo) == 0))
		{
			ft_init(&filo);
			i = -1;
			pthread_create(&monitor_thread, NULL, monitor, &filo);
			while (++i < filo.num_philo)
				pthread_join(filo.filosofos[i], NULL);
			i = -1;
			while (++i < filo.num_philo)
				pthread_mutex_destroy(&filo.garfos[i]);
		}
	}
	else
		error_stop("Error: ./philo 5 800 200 200");
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 08:16:48 by hmateque          #+#    #+#             */
/*   Updated: 2024/09/27 09:34:34 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	int				i;
	t_philo_info	filo;
	struct timeval	start;

	if (ac == 5 || ac == 6)
	{
		if ((checker_of_arguments(ac, av, &filo) == 0))
		{
			ft_init(&filo, &start);
			i = -1;
			while (++i < filo.num_philo)
				pthread_join(filo.filosofos[i], NULL);
			i = -1;
			while (++i < filo.num_philo)
				pthread_mutex_destroy(&filo.garfos[i]);
		}
	}
	else
		error_stop("Error: ./philo num_philopher time_to_die time_to_eat time_to_sleep [num_of_each]");
	// free(filo.filosofos);
	// free(filo.garfos);
	// free(filo.ids);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 08:16:48 by hmateque          #+#    #+#             */
/*   Updated: 2024/10/07 12:47:43 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_philos(t_philo_info *filo, t_arg_info *info_args)
{
	int	i;

	i = -1;
	while (++i < info_args->num_philo)
	{
		filo[i].last_meal_time = 0;
		filo[i].number_each = info_args->number_of_each;
		filo[i].philo_state = 1;
		filo[i].id = i;
		filo[i].info = info_args;
	}
}

int	main(int ac, char **av)
{
	t_philo_info	*filo;
	t_arg_info		info_args;
	pthread_t		monitor_thread;

	if (ac == 5 || ac == 6)
	{
		if ((checker_of_arguments(ac, av, &info_args) == 0))
		{
			filo = (t_philo_info *)malloc(sizeof(t_philo_info)
					* info_args.num_philo);
			if (filo == NULL)
				return (1);
			set_philos(filo, &info_args);
			if (!ft_init(filo, &info_args))
			{
				pthread_create(&monitor_thread, NULL, monitor, filo);
				cleanup(filo, &info_args);
				pthread_join(monitor_thread, NULL);
			}
		}
	}
	else
		error_stop("Error: ./philo 5 800 200 200");
	return (0);
}

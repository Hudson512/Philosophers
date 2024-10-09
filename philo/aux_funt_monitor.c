/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_2_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:12:47 by hmateque          #+#    #+#             */
/*   Updated: 2024/10/09 09:51:28 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_death(t_philo_info *filo, int i)
{
	long int	current_time;

	current_time = get_current_time();
	if ((current_time - filo[i].last_meal_time) > filo->info->time_to_die)
	{
		filo->info->flag_de_morte = 1;
		printf("\033[0;31m%ldms %d died\033[0m\n", (current_time
				- filo->info->start), (i + 1));
	}
}

int	check_philo_state(t_philo_info *filo, int i)
{
	if (filo[i].philo_state == 1)
	{
		check_death(filo, i);
		if (filo->info->flag_de_morte)
			return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:37:15 by hmateque          #+#    #+#             */
/*   Updated: 2024/10/02 08:56:40 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	checker_value_of_arguments(char *av)
{
	int	value;

	value = atoi(av);
	if (value <= 0)
		return (1);
	return (0);
}

int	checker_of_arguments(int ac, char **av, t_philo_info *filo)
{
	int	i;
	int	j;

	i = 0;
	while (++i < ac)
	{
		j = -1;
		while (av[i][++j])
		{
			if (is_digit(av[i][j]))
				return (error_stop("Error in arguments!"));
		}
		if (checker_value_of_arguments(av[i]))
			return (error_stop("Error in arguments!"));
		add_value(filo, ft_atoi(av[i]), i);
	}
	if (ac < 6)
		filo->number_of_each = 0;
	return (0);
}

void	check_num_philo(t_philo_info *filo, int id)
{
	if (filo->num_philo == 1)
	{
		while (!filo->flag_de_morte)
			usleep(filo->time_to_die);
		pthread_mutex_unlock(&filo->garfos[id]);
	}
}

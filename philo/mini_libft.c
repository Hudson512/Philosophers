/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_libft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:30:54 by hmateque          #+#    #+#             */
/*   Updated: 2024/10/02 11:49:16 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (0);
	return (1);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	nb;

	i = 0;
	while (nptr[i] == ' ' || nptr[i] == '\f' || nptr[i] == '\n'
		|| nptr[i] == '\r' || nptr[i] == '\t' || nptr[i] == '\v')
		i++;
	sign = 1;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	nb = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + nptr[i] - '0';
		i++;
	}
	return (nb * sign);
}

void	print_datas(t_philo_info *filo)
{
	printf("N de filo = %d\n", filo->num_philo);
	printf("T para morrer = %ld\n", filo->time_to_die);
	printf("T para comer = %ld\n", filo->time_to_eat);
	printf("T para dormir = %ld\n", filo->time_to_sleep);
	printf("N de refeicao = %d\n", filo->number_of_each);
}

int	print_status(char *str, int id, t_philo_info *filo)
{
	if (filo->flag_de_morte)
	{
		pthread_mutex_unlock(&filo->garfos[id]);
		pthread_mutex_unlock(&filo->garfos[(id + 1) % filo->num_philo]);
		return (1);
	}
	printf("%ldms %d %s\n", (get_current_time() - filo->start), (id + 1), str);
	return (0);
}

int	print_status_eating(char *str, int id, t_philo_info *filo)
{
	if (filo->flag_de_morte)
	{
		pthread_mutex_unlock(&filo->garfos[id]);
		pthread_mutex_unlock(&filo->garfos[(id + 1) % filo->num_philo]);
		return (1);
	}
	printf("\033[0;34m%ldms %d %s\033[0m\n", (get_current_time() - filo->start),
		(id + 1), str);
	return (0);
}

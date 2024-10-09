/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_libft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:30:54 by hmateque          #+#    #+#             */
/*   Updated: 2024/10/09 09:42:14 by hmateque         ###   ########.fr       */
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
	printf("ID de filo = %d\n", filo->id);
	printf("N de refei.. = %d\n", filo->number_each);
	printf("........Info........\n");
	printf("Total de filo = %d\n", filo->info->num_philo);
	printf("Tempo para Morrer = %ld\n", filo->info->time_to_die);
	printf("Tempo para Comer = %ld\n", filo->info->time_to_eat);
	printf("Tempo para Dormir = %ld\n", filo->info->time_to_sleep);
	printf("........FIM.........\n");
}

int	print_status(char *str, int id, t_philo_info *filo)
{
	pthread_mutex_lock(&filo->info->death_mutex);
	if (filo->info->flag_de_morte)
	{
		pthread_mutex_unlock(&filo->info->death_mutex);
		return (1);
	}
	printf("%ldms %d %s\n", (get_current_time() - filo->info->start), (id + 1),
		str);
	pthread_mutex_unlock(&filo->info->death_mutex);
	return (0);
}

int	print_status_eating(char *str, int id, t_philo_info *filo)
{
	pthread_mutex_lock(&filo->info->death_mutex);
	if (filo->info->flag_de_morte)
	{
		pthread_mutex_unlock(&filo->info->death_mutex);
		return (1);
	}
	printf("\033[0;34m%ldms %d %s\033[0m\n", (get_current_time()
			- filo->info->start), (id + 1), str);
	pthread_mutex_unlock(&filo->info->death_mutex);
	return (0);
}

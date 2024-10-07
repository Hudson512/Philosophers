/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 10:24:30 by hmateque          #+#    #+#             */
/*   Updated: 2024/10/07 13:16:27 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_philo_info *filos, t_arg_info *info_args)
{
	int	i;

	i = -1;
	while (++i < info_args->num_philo)
		pthread_join(filos[i].filosofos, NULL);
	i = -1;
	while (++i < info_args->num_philo)
		pthread_mutex_destroy(&info_args->garfos[i]);
	free(filos);
	free(info_args->garfos);
}

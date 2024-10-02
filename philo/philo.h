/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 08:16:43 by hmateque          #+#    #+#             */
/*   Updated: 2024/10/02 11:48:00 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		*filosofos;
	pthread_mutex_t	*garfos;
	int				num_philo;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	int				number_of_each;
	// dados extras
	long int		*last_meal_time;
	int				*arr_number_each;
	long int		start;
	int				flag_de_morte;
	// fim dos dados extras
}					t_philo_info;

typedef struct s_filo_param
{
	t_philo_info	*filo;
	int				id;
}					t_filo_param;

void				*filosofar_1(void *arg);
void				*filosofar_2(void *arg);
void				*monitor(void *arg);
void				print_datas(t_philo_info *filo);
void				check_num_philo(t_philo_info *filo, int id);
int					print_status(char *str, int id, t_philo_info *filo);
int					print_status_eating(char *str, int id, t_philo_info *filo);
void				add_value(t_philo_info *filo, int value, int i);
int					is_digit(char c);
int					ft_atoi(const char *nptr);
int					error_stop(char *str);
int					ft_init(t_philo_info *filo);
int					checker_value_of_arguments(char *av);
int					checker_of_arguments(int ac, char **av, t_philo_info *filo);
long int			get_time_end(struct timeval *start);
long int			get_current_time(void);

#endif
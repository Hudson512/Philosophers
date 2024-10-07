/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 08:16:43 by hmateque          #+#    #+#             */
/*   Updated: 2024/10/07 13:49:00 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_filo_arguments
{
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	long int		start;
	int				number_of_each;
	int				flag_de_morte;
	int				num_philo;
	pthread_mutex_t	*garfos;
}					t_arg_info;

typedef struct s_philo
{
	pthread_t		filosofos;
	long int		last_meal_time;
	int				number_each;
	int				philo_state;
	int				id;
	t_arg_info		*info;
}					t_philo_info;

void				*filosofar_1(void *arg);
void				*filosofar_2(void *arg);
void				*monitor(void *arg);
void				cleanup(t_philo_info *filos, t_arg_info *info_args);
void				set_philos(t_philo_info *filo, t_arg_info *info_args);
void				print_datas(t_philo_info *filo);
void				check_num_philo(t_philo_info *filo, int id);
int					print_status(char *str, int id, t_philo_info *filo);
int					print_status_eating(char *str, int id, t_philo_info *filo);
void				add_value(t_arg_info *info_args, int value, int i);
int					is_digit(char c);
int					ft_atoi(const char *nptr);
int					error_stop(char *str);
int					check_all_philo(t_philo_info *filo);
int					ft_init(t_philo_info *filo, t_arg_info *info_args);
int					checker_value_of_arguments(char *av);
int					checker_of_arguments(int ac, char **av,
						t_arg_info *info_args);
long int			get_time_end(struct timeval *start);
long int			get_current_time(void);

#endif
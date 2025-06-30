/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_header.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:41:29 by mel-houa          #+#    #+#             */
/*   Updated: 2025/06/30 18:50:36 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_HEADER_H
# define PHILO_HEADER_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_info
{
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				number_of_philo;
	int				time_to_think;

	int				number_of_rep;
	long			gen_time_start;
	int				full_food;
	int				end;
	pthread_mutex_t	protect_meal;
	pthread_mutex_t	protect;
	pthread_mutex_t	*forks;
	pthread_mutex_t	protect_printf;
}					t_philo_info;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	pthread_t		thr;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	long			last_meal_time;

	t_philo_info	*genr_info;
}					t_info_of_each_philo;

int					is_die(t_info_of_each_philo *ph);
void				ft_usleep(t_info_of_each_philo *ph, int time);
int					is_valide_arg(int num_of_arg, char **arg);
int					ft_atoi(char *s);
int					is_space(char c);
long				get_current_time(void);
void				*routine(void *arg);
void				ft_print(t_info_of_each_philo *ph, char *s);
int					ft_eat(t_info_of_each_philo *ph);
int					ft_sleep(t_info_of_each_philo *ph);
int					ft_think(t_info_of_each_philo *ph);
int					get_fork(t_info_of_each_philo *ph);
int					creat_join_th(t_info_of_each_philo *philos,
						t_philo_info *info);
int					initial_data(t_info_of_each_philo *philos,
						t_philo_info *info);
void				*monitor(void *arg);
void				clean_mutex(t_info_of_each_philo *philos,
						t_philo_info *info, int count);
int					create_fork(t_philo_info *info,
						t_info_of_each_philo *philo);
void				fill_info_of_philo(int ac, char **av,
						t_philo_info *info_of_phillo);
#endif
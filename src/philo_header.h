/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_header.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:41:29 by mel-houa          #+#    #+#             */
/*   Updated: 2025/05/26 20:24:18 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_HEADER_H
#define  PHILO_HEADER_H


#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>







typedef struct s_info
{
    int time_to_eat;
    int time_to_die;
    int time_to_sleep;
    int number_of_philo;
    int number_of_rep;
    long gen_time_start;
    pthread_mutex_t *forks;
} t_philo_info;



typedef struct s_philo
{
    int ID;
    pthread_t thr;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *left_fork;
    long last_meal_time;
    
    t_philo_info *genr_info;
} t_info_of_each_philo;


int is_valide_arg(int num_of_arg, char **arg);
int ft_atoi(char *s);
int is_space(char c);
long get_current_time();
void *routine(void *arg);
int creat_join_th(t_info_of_each_philo *philos, t_philo_info *info);
int initial(t_info_of_each_philo **philos, t_philo_info *info);
void clean_mutex(t_info_of_each_philo *philos, t_philo_info *info);
int create_fork(t_philo_info *info, t_info_of_each_philo *philo);
void fill_info_of_philo(int ac, char **av, t_philo_info *info_of_phillo);

#endif
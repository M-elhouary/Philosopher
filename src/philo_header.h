/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_header.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:41:29 by mel-houa          #+#    #+#             */
/*   Updated: 2025/05/22 01:18:11 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_HEADER_H
#define  PHILO_HEADER_H


#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <pthread.h>





typedef struct s_philo
{
    int ID;
    pthread_t thr;
    pthread_mutex_t right_fork;
    pthread_mutex_t left_fork;
    
} t_info_of_each_philo;


typedef struct s_info
{
    int time_to_eat;
    int time_to_die;
    int time_to_sleep;
    int number_of_philo;
    int number_of_rep;
    pthread_mutex_t *forks;
    t_info_of_each_philo *philo_info;
} t_philo_info;




int is_valide_arg(int num_of_arg, char **arg);
int ft_atoi(char *s);
int is_space(char c);
void fill_info_of_philo(int ac, char **av, t_philo_info *info_of_phillo);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 21:41:52 by mel-houa          #+#    #+#             */
/*   Updated: 2025/06/19 19:45:26 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo_header.h"

long get_current_time()
{
    struct timeval tv;
    long second;
    long microsecond;
    long millisecond;

    gettimeofday(&tv, NULL);
    second = tv.tv_sec;
    microsecond = tv.tv_usec;
    millisecond = (second * 1000) + (microsecond / 1000);
    return (millisecond);
}

void clean_mutex(t_info_of_each_philo *philos, t_philo_info *info)
{
    int index;

    index = 0;
    while(index < info->number_of_philo)
    {
        pthread_mutex_destroy(&info->forks[index]);
        index++;
    }
    pthread_mutex_destroy(&info->protect_meal);
    pthread_mutex_destroy(&info->protect);
    pthread_mutex_destroy(&info->protect_printf);
    free(info->forks);
    free(philos);
}

int get_fork(t_info_of_each_philo *ph)
{
    long now;
    pthread_mutex_lock(&ph->genr_info->protect);
    if (ph->genr_info->end == 1)
    {
        pthread_mutex_unlock(&ph->genr_info->protect);
        return (1);
    }
    pthread_mutex_unlock(&ph->genr_info->protect);
    if (ph->ID % 2 == 0)
    {
        // Even: right first
        pthread_mutex_lock(ph->right_fork);
        now = get_current_time() - ph->genr_info->gen_time_start;
        
        pthread_mutex_lock(&ph->genr_info->protect_printf);
        printf("%ld %d has taken a fork\n", now, ph->ID);
        pthread_mutex_unlock(&ph->genr_info->protect_printf);
        
        pthread_mutex_lock(ph->left_fork);
        now = get_current_time() - ph->genr_info->gen_time_start;
        
        pthread_mutex_lock(&ph->genr_info->protect_printf);
        printf("%ld %d has taken a fork\n", now, ph->ID);
        pthread_mutex_unlock(&ph->genr_info->protect_printf);
    }
    else
    {
        // Odd: left first
        pthread_mutex_lock(ph->left_fork);
        now = get_current_time() - ph->genr_info->gen_time_start;
        
        pthread_mutex_lock(&ph->genr_info->protect_printf);
        printf("%ld %d has taken a fork\n", now, ph->ID);
        pthread_mutex_unlock(&ph->genr_info->protect_printf);
        
        if (ph->genr_info->number_of_philo == 1)
           return (pthread_mutex_unlock(ph->left_fork),1);
        pthread_mutex_lock(ph->right_fork);
        now = get_current_time() - ph->genr_info->gen_time_start;
        
        pthread_mutex_lock(&ph->genr_info->protect_printf);
        printf("%ld %d has taken a fork\n", now, ph->ID);
        pthread_mutex_unlock(&ph->genr_info->protect_printf);      
    }
    return 0;
}
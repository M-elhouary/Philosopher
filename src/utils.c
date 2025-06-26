/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 21:41:52 by mel-houa          #+#    #+#             */
/*   Updated: 2025/06/26 21:39:28 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo_header.h"


void ft_print(t_info_of_each_philo *ph, char *s)
{
    long now;
 

     pthread_mutex_lock(&ph->genr_info->protect);
    if (ph->genr_info->end == 1)
    {
        pthread_mutex_unlock(&ph->genr_info->protect);
        return;
    }
    pthread_mutex_unlock(&ph->genr_info->protect);
    
   pthread_mutex_lock(&ph->genr_info->protect_printf);
   now = ph->last_meal_time - ph->genr_info->gen_time_start;
   printf("%ld %d %s\n", now, ph->ID, s);
   pthread_mutex_unlock(&ph->genr_info->protect_printf);
}
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
        ft_print(ph, "has taken a fork");
        pthread_mutex_lock(ph->left_fork);
        ft_print(ph, "has taken a fork");
    }
    else
    {
        // Odd: left first
        pthread_mutex_lock(ph->left_fork);
        ft_print(ph, "has taken a fork");
        if (ph->genr_info->number_of_philo == 1)
           return (pthread_mutex_unlock(ph->left_fork),1);
        pthread_mutex_lock(ph->right_fork);
        ft_print(ph, "has taken a fork");     
    }
    return 0;
}
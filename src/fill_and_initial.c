/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_and_initial.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 21:40:16 by mel-houa          #+#    #+#             */
/*   Updated: 2025/06/26 21:56:30 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo_header.h"

void fill_info_of_philo(int ac, char **av, t_philo_info *info_of_phillo)
{
    
    info_of_phillo->number_of_philo = ft_atoi(av[1]);
    info_of_phillo->time_to_die = ft_atoi(av[2]);
    info_of_phillo->time_to_eat = ft_atoi(av[3]);
    info_of_phillo->time_to_sleep = ft_atoi(av[4]);
    info_of_phillo->time_to_think = 0;
    if(info_of_phillo->number_of_philo % 2)
        info_of_phillo->time_to_think = info_of_phillo->time_to_eat;
    info_of_phillo->number_of_rep = -1;
    if(ac == 6)
        info_of_phillo->number_of_rep = ft_atoi(av[5]);

}


int initial(t_info_of_each_philo  *philos, t_philo_info *info)
{
    int count;
    
    info->full_food = 0;
    info->end = 0;
    count = 0;
    while(count < info->number_of_philo)
    {
        (philos)[count].ID = count + 1;
         (philos)[count].eat_count = 0;
        (philos)[count].genr_info   = info;
       (philos)[count].last_meal_time = get_current_time();
        (philos)[count].left_fork = &info->forks[count];
		if(count == info->number_of_philo  - 1)
            (philos)[count].right_fork = &info->forks[0];
		else
            (philos)[count].right_fork = &info->forks[count + 1];
        count++;
    }
    if(pthread_mutex_init(&info->protect_printf, NULL) != 0)
        return ((write(2, "Mutex init failed\n", 18)),1);
    if(pthread_mutex_init(&info->protect_meal, NULL) != 0)
        return ((write(2, "Mutex init failed\n", 18)),1);
    if(pthread_mutex_init(&info->protect, NULL) != 0)
        return ((write(2, "Mutex init failed\n", 18)),1);
    return (0);
}
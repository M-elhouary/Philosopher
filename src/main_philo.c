/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:40:19 by mel-houa          #+#    #+#             */
/*   Updated: 2025/06/20 21:34:20 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

void *routine(void *arg)
{
    t_info_of_each_philo *ph ;
    long now;
    
    ph = arg;
    if(ph->ID % 2)
    {
        
    // pthread_mutex_lock(&ph->genr_info->protect_printf);
    // now = get_current_time() - ph->genr_info->gen_time_start;
    // printf("%ld %d is thinking\n", now, ph->ID);
    // pthread_mutex_unlock(&ph->genr_info->protect_printf);
        ft_print(ph, "thinking");
        usleep(ph->genr_info->time_to_eat );
    }
    while (1)
    {
        pthread_mutex_lock(&ph->genr_info->protect);
        if (ph->genr_info->end == 1)
        {
            pthread_mutex_unlock(&ph->genr_info->protect);
                break;
        }
        pthread_mutex_unlock(&ph->genr_info->protect);
        if(get_fork(ph) == 1)
            break;
        if(ft_eat(ph) == 1)
            break;
        if(ft_sleep(ph) == 1)
            break;
        if(ft_think(ph) == 1)
                 break;
    }
    return (NULL);
}

int main(int ac, char **av)
{
    // general info 
    t_philo_info info;
    // info of each philo
    t_info_of_each_philo *philos;
    int count; 
    
    count = 0;
    // check arg valid or not 
    if(is_valide_arg(ac, av) == 0)
        return ((write(2, "Error: INVALIDE ARGUMENT\n", 26)),1);
    //fill info of philosopher
    fill_info_of_philo(ac, av, &info);
    // allocet her for all philosopher 
    philos = malloc(sizeof(t_info_of_each_philo) * info.number_of_philo);
        if (!philos)
            return (free(info.forks), 1);
    // initial mutex 
    if(pthread_mutex_init(&info.protect_meal, NULL) != 0)
        return ((write(2, "Mutex init failed\n", 18)),1);
    if(pthread_mutex_init(&info.protect, NULL) != 0)
        return ((write(2, "Mutex init failed\n", 18)),1);
    if (create_fork(&info, philos))
        return (free(info.forks), free(philos), 1);
    if (initial(philos, &info))
        return (free(philos), 1);
    if(creat_join_th(philos, &info))
        return (1);
    clean_mutex(philos, &info);
    return 0;
}


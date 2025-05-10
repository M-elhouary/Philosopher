/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:40:19 by mel-houa          #+#    #+#             */
/*   Updated: 2025/05/09 23:54:05 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo_header.h"


void fill_info_of_philo(int ac, char **av, t_philo_info *info_of_phillo)
{
    
    info_of_phillo->number_of_philo = ft_atoi(av[1]);
    info_of_phillo->time_to_die = ft_atoi(av[2]);
    info_of_phillo->time_to_eat = ft_atoi(av[3]);
    info_of_phillo->time_to_sleep = ft_atoi(av[4]);
    info_of_phillo->number_of_rep = -1;
    if(ac == 6)
        info_of_phillo->number_of_rep = ft_atoi(av[5]);

}

void initial(t_info_of_each_philo *philos)
{
    int count;
    
    count = 0;
    while(count < philos->info->number_of_philo)
    {
        philos[count].ID = count + 1;
        philos[count].left_fork = count;
        philos[count].right_fork = count + 1;
    }
}
void routine(void *p)
{
    
}
int main(int ac, char **av)
{
    t_philo_info info;
    t_info_of_each_philo *philos;
    int count; 
    
    count = 0;
    if(is_valide_arg(ac, av) == 0)
    {
        printf("INVALIDE ARGUMENT :(\n");
        return (1);
    }
    fill_info_of_philo(ac, av, &info);
    philos = malloc(sizeof(t_info_of_each_philo) * (info.number_of_philo));
    info.forks = malloc(sizeof(pthread_mutex_t) * info.number_of_philo);

    while(count < info.number_of_philo)
    {
        pthread_mutex_init(&info.forks[count++], NULL);
    }
    count = 0;
    while(count < info.number_of_philo)
    {
        pthread_create(&philos->thr, NULL, routine(), NULL);
        count++;
    }
    count = 0;
    while(count < info.number_of_philo)
    {
        pthread_join(&philos[count++].thr, NULL);
    }
    return (0);
}
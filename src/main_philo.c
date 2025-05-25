/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:40:19 by mel-houa          #+#    #+#             */
/*   Updated: 2025/05/24 23:36:17 by mel-houa         ###   ########.fr       */
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

void initial(t_info_of_each_philo **philos, t_philo_info *info)
{
    int count;
    
    *philos = malloc(sizeof(t_info_of_each_philo) * (info->number_of_philo));
    if(!*philos)
        exit(EXIT_FAILURE);
    count = 0;
    while(count < info->number_of_philo)
    {
        (*philos)[count].ID = count + 1;
        (*philos)[count].left_fork = info->forks[count];
		if(count == info->number_of_philo  - 1)
        (*philos)[count].right_fork = info->forks[0];
		else
        (*philos)[count].right_fork = info->forks[count + 1];
        count++;
    }
}
void *routine(void *philo)
{
    t_info_of_each_philo *philo_info;
	philo_info = (t_info_of_each_philo *)philo;
    
    while(1317){
        pthread_mutex_lock(&philo_info->left_fork);
        printf("%d  has taken a fork\n", philo_info->ID);
        pthread_mutex_lock(&philo_info->right_fork);
        printf("%d  has taken a fork\n", philo_info->ID);
        printf("%d  has eating\n", philo_info->ID);
        pthread_mutex_unlock(&philo_info->left_fork);
        pthread_mutex_unlock(&philo_info->right_fork);
    }
        
    return NULL;
}


void create_fork(t_philo_info *info)
{
    int count;
    
    count = 0;
    info->forks = malloc(sizeof(pthread_mutex_t) * info->number_of_philo);
    if(!info->forks)
        exit(EXIT_FAILURE);
    while(count < info->number_of_philo)
        pthread_mutex_init(&info->forks[count++], NULL);
    
}

void creat_join_th(t_info_of_each_philo *philos, t_philo_info *info)
{
    int count;
    
    count = 0;
    while(count < info->number_of_philo)
    {
        if(pthread_create(&philos[count].thr, NULL, routine, &philos[count]) != 0)
        {
                perror("pthread_create faild");
                exit(EXIT_FAILURE);
            }
            count++;
    }
    count = 0;
    while(count < info->number_of_philo)
    {
        pthread_join((philos)[count].thr, NULL);
            count++;
    }

}
void clean_mutex(t_info_of_each_philo *philos, t_philo_info info)
{
    int index;

    index = 0;
    while(index < info.number_of_philo)
    {
        pthread_mutex_destroy(&info.forks[index]);
        index++;
    }
    free(info.forks);
    free(philos);
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
    create_fork(&info);
    initial(&philos, &info);
    creat_join_th(philos, &info);
    clean_mutex(philos, info);
    
    return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:40:19 by mel-houa          #+#    #+#             */
/*   Updated: 2025/05/22 03:40:41 by mel-houa         ###   ########.fr       */
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

void initial(t_philo_info *philos)
{
    int count;
    
    count = 0;
    while(count <= philos->number_of_philo)
    {
        count++;
		philos->philo_info[count].ID = count;
        philos->philo_info[count].left_fork = philos->forks[count];
		if(count ==  philos->number_of_philo)
        	philos->philo_info[count].right_fork = philos->forks[0];
		else
        	philos->philo_info[count].right_fork = philos->forks[count + 1];
    }
}
void *routine(void *philo)
{
    t_info_of_each_philo *philo_info;
	philo_info = (t_info_of_each_philo *)philo;

	while(1337)
	{
		pthread_mutex_lock(&philo_info->left_fork);
		printf("%d  has taken a fork\n", philo_info->ID);
		pthread_mutex_lock(&philo_info->right_fork);
		printf("%d  has taken a fork\n", philo_info->ID);
        pthread_mutex_unlock(&philo_info->left_fork);
        pthread_mutex_unlock(&philo_info->right_fork);
	}
    
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
    philos = malloc(sizeof(t_philo_info) * (info.number_of_philo));
    info.forks = malloc(sizeof(pthread_mutex_t) * info.number_of_philo);

    while(count < info.number_of_philo)
    {
        pthread_mutex_init(&info.forks[count++], NULL);
    }
    count = 0;
    while(count < info.number_of_philo)
    {
        pthread_create(&philos[count].thr, NULL, routine, &philos[count]);
        count++;
    }
    count = 0;
    while(count < info.number_of_philo)
    {
        pthread_join(philos[count++].thr, NULL);
    }
    return (0);
}
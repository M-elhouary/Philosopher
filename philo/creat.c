/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 21:40:45 by mel-houa          #+#    #+#             */
/*   Updated: 2025/07/12 15:29:42 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

int	create_fork(t_philo_info *info, t_info_of_each_philo *philo)
{
	int	count;

	count = 0;
	info->forks = malloc(sizeof(pthread_mutex_t) * info->number_of_philo);
	if (!info->forks)
		return (1);
	while (count < info->number_of_philo)
	{
		if (pthread_mutex_init(&info->forks[count++], NULL) != 0)
		{
			clean_mutex(philo, info, count);
			return (1);
		}
	}
	return (0);
}

int	creat_th(t_info_of_each_philo *philos, t_philo_info *info)
{
	int	count;

	count = 0;
	while (count < info->number_of_philo)
	{
		pthread_mutex_lock(&info->protect_meal);
		philos[count].last_meal_time = get_current_time();
		pthread_mutex_unlock(&info->protect_meal);
		if (pthread_create(&philos[count].thr, NULL, routine,
				&philos[count]) != 0)
		{
			printf("pthread_create faild");
			return (1);
		}
		count++;
	}
	return (0);
}

int	creat_join_th(t_info_of_each_philo *philos, t_philo_info *info)
{
	int			count;
	pthread_t	monitor_thread;

	count = 0;
	info->gen_time_start = get_current_time();
	if (creat_th(philos, info) == 1)
		return (1);
	usleep(1000);
	if (pthread_create(&monitor_thread, NULL, monitor, philos) != 0)
		return (write(2, "Error: monitor thread failed\n", 30), 1);
	count = 0;
	while (count < info->number_of_philo)
	{
		pthread_join(philos[count].thr, NULL);
		count++;
	}
	if (philos->genr_info->number_of_rep == 0)
	{
		pthread_detach(monitor_thread);
		return (clean_mutex(philos, info, philos->genr_info->number_of_philo),
			1);
	}
	if (pthread_join(monitor_thread, NULL) != 0)
		return (write(2, "Error: monitor join failed\n", 27), 1);
	return (0);
}

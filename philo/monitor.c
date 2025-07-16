/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 21:41:12 by mel-houa          #+#    #+#             */
/*   Updated: 2025/07/16 23:57:22 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

int	is_die(t_info_of_each_philo *ph)
{
	int	end_flag;

	pthread_mutex_lock(&ph->genr_info->protect);
	end_flag = ph->genr_info->end;
	pthread_mutex_unlock(&ph->genr_info->protect);
	return (end_flag);
}

int	fuul_food(t_info_of_each_philo *ph)
{
	if (ph->genr_info->number_of_rep > 0)
	{
		pthread_mutex_lock(&ph->genr_info->protect_meal);
		if (ph->genr_info->full_food == ph->genr_info->number_of_philo)
		{
			pthread_mutex_lock(&ph->genr_info->protect);
			ph->genr_info->end = 1;
			pthread_mutex_unlock(&ph->genr_info->protect);
			pthread_mutex_unlock(&ph->genr_info->protect_meal);
			return (1);
		}
		else
			pthread_mutex_unlock(&ph->genr_info->protect_meal);
	}
	return (0);
}

int	check_time_die(int i, t_info_of_each_philo *ph)
{
	long	now;
	long	time_stamp;

	while (i < ph[0].genr_info->number_of_philo)
	{
		pthread_mutex_lock(&ph->genr_info->protect_meal);
		now = get_current_time();
		if (now - ph[i].last_meal_time > ph[i].genr_info->time_to_die)
		{
			pthread_mutex_lock(&ph->genr_info->protect);
			pthread_mutex_unlock(&ph->genr_info->protect_meal);
			ph->genr_info->end = 1;
			pthread_mutex_unlock(&ph->genr_info->protect);
			pthread_mutex_lock(&ph->genr_info->protect_printf);
			time_stamp = get_current_time() - ph->genr_info->gen_time_start;
			printf("%ld %d died\n", time_stamp, ph[i].id);
			pthread_mutex_unlock(&ph->genr_info->protect_printf);
			return (1);
		}
		else
			pthread_mutex_unlock(&ph->genr_info->protect_meal);
		i++;
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_info_of_each_philo	*ph;
	int						i;
	long					now;
	long					time_stamp;

	ph = (t_info_of_each_philo *)arg;
	if (ph->genr_info->number_of_rep == 0)
		return (NULL);
	while (1)
	{
		i = 0;
		if (check_time_die(i, ph) == 1)
			return (NULL);
		if (fuul_food(ph) == 1)
			return (NULL);
		usleep(100);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 21:41:52 by mel-houa          #+#    #+#             */
/*   Updated: 2025/06/30 18:54:01 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

void	ft_print(t_info_of_each_philo *ph, char *s)
{
	long	now;

	if (is_die(ph))
		return ;
	pthread_mutex_lock(&ph->genr_info->protect_printf);
	now = get_current_time() - ph->genr_info->gen_time_start;
	if (is_die(ph))
	{
		pthread_mutex_unlock(&ph->genr_info->protect_printf);
		return ;
	}
	printf("%ld %d %s\n", now, ph->id, s);
	pthread_mutex_unlock(&ph->genr_info->protect_printf);
}

long	get_current_time(void)
{
	struct timeval	tv;
	long			second;
	long			microsecond;
	long			millisecond;

	gettimeofday(&tv, NULL);
	second = tv.tv_sec;
	microsecond = tv.tv_usec;
	millisecond = (second * 1000) + (microsecond / 1000);
	return (millisecond);
}

void	clean_mutex(t_info_of_each_philo *philos, t_philo_info *info, int count)
{
	int	index;

	index = 0;
	while (index < count)
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

int	get_fork(t_info_of_each_philo *ph)
{
	long	now;

	if (is_die(ph))
		return (1);
	if (ph->id % 2 == 0)
	{
		pthread_mutex_lock(ph->right_fork);
		ft_print(ph, "has taken a fork");
		pthread_mutex_lock(ph->left_fork);
		ft_print(ph, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(ph->left_fork);
		ft_print(ph, "has taken a fork");
		pthread_mutex_lock(ph->right_fork);
		ft_print(ph, "has taken a fork");
	}
	return (0);
}

void	ft_usleep(t_info_of_each_philo *ph, int time)
{
	long	start;
	long	now;

	start = get_current_time();
	while (1)
	{
		if (is_die(ph))
			break ;
		now = get_current_time();
		if (now - start >= time)
			break ;
		usleep(100);
	}
}

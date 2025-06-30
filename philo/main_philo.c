/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:40:19 by mel-houa          #+#    #+#             */
/*   Updated: 2025/06/30 02:16:48 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

void	*routine(void *arg)
{
	t_info_of_each_philo	*ph;
	long					now;

	ph = arg;
	if (ph->genr_info->number_of_philo == 1)
	{
		pthread_mutex_lock(ph->left_fork);
		ft_print(ph, "has taken a fork");
		while (1)
		{
			if (is_die(ph))
			{
				pthread_mutex_unlock(ph->left_fork);
				return (NULL);
			}
			usleep(100);
		}
	}
	if (ph->ID % 2)
	{
		ft_print(ph, "thinking");
		ft_usleep(ph, ph->genr_info->time_to_eat);
		// usleep(ph->genr_info->time_to_eat * 100);
	}
	while (1)
	{
		if (is_die(ph) == 1)
			break ;
		if (get_fork(ph) == 1)
			break ;
		if (ft_eat(ph) == 1)
			break ;
		if (ft_sleep(ph) == 1)
			break ;
		if (ft_think(ph) == 1)
			break ;
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_philo_info			info;
	t_info_of_each_philo	*philos;
	int						count;

	// general info
	// info of each philo
	count = 0;
	if (ac > 1) // check arg valid or not
	{
		if (is_valide_arg(ac, av) == 0)
			return ((write(2, "Error: INVALIDE ARGUMENT\n", 26)), 1);
		// fill info of philosopher
		fill_info_of_philo(ac, av, &info);
		// allocet her for all philosopher
		philos = malloc(sizeof(t_info_of_each_philo) * info.number_of_philo);
		if (!philos)
			return (1);
		// initial mutex
		if (create_fork(&info, philos))
			return (free(philos), 1);
		if (initial(philos, &info))
			return (free(info.forks), free(philos), 1);
		if (creat_join_th(philos, &info))
			return (1);
		clean_mutex(philos, &info, info.number_of_philo);
	}
	return (0);
}

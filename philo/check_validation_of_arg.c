/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validation_of_arg.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:47:14 by mel-houa          #+#    #+#             */
/*   Updated: 2025/06/30 18:39:09 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

int	is_space(char c)
{
	return (c == 9 || c == 10 || c == 11 || c == 12 || c == 13 || c == 32);
}

int	ft_atoi(char *s)
{
	long	res;
	int		index;

	index = 0;
	res = 0;
	if (s[index] == '+' || s[index] == '-')
		return (-1);
	while (s[index])
	{
		if (((s[index] < '0' || s[index] > '9') && !is_space(s[index])))
			return (-1);
		index++;
	}
	index = 0;
	while (s[index])
	{
		if (s[index] >= '0' && s[index] <= '9')
		{
			res = res * 10 + (s[index] - 48);
			if (res > INT_MAX || res < 0)
				return (-1);
		}
		index++;
	}
	return (res);
}

int	is_valide_arg(int num_of_arg, char **arg)
{
	int	count;

	count = 1;
	if (ft_atoi(arg[1]) == 0)
		return (0);
	if (num_of_arg == 6 || num_of_arg == 5)
	{
		while (count < num_of_arg)
		{
			if (ft_atoi(arg[count]) == -1)
				return (0);
			count++;
		}
		return (1);
	}
	return (0);
}

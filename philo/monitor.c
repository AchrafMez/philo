/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:21:29 by amezioun          #+#    #+#             */
/*   Updated: 2024/08/06 15:07:22 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_on_lmakla(t_data *data)
{
	pthread_mutex_lock(&data->lmakla_mut);
	data->lmakla++;
	pthread_mutex_unlock(&data->lmakla_mut);
}

int	get_dead(t_data *data)
{
	int	is_die;

	pthread_mutex_lock(&data->dead_mut);
	is_die = data->dead;
	pthread_mutex_unlock(&data->dead_mut);
	return (is_die);
}

int	monitor(t_data *data)
{
	int				i;
	unsigned long	last_meal_t;

	i = 0;
	while (i < data->philo_num)
	{
		if ((get_lmakla(data) == 0))
			return (2);
		pthread_mutex_lock(&data->last_time);
		last_meal_t = data->philos[i].last_meal_time;
		pthread_mutex_unlock(&data->last_time);
		if (ft_get_time_of_day() - last_meal_t >= data->time_to_die)
		{
			pthread_mutex_lock(&data->dead_mut);
			data->dead = 1;
			printf("%lu %d died\n", ft_get_time_of_day() - data->start_time,
				data->philos[i].philo_id);
			pthread_mutex_unlock(&data->dead_mut);
			return (0);
		}
		i++;
	}
	return (1);
}

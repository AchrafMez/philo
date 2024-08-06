/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:06:39 by amezioun          #+#    #+#             */
/*   Updated: 2024/08/05 22:18:52 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	ft_get_time_of_day(void)
{
	unsigned long	mili_seconds;
	struct timeval	time;

	gettimeofday(&time, NULL);
	mili_seconds = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (mili_seconds);
}

void	ft_usleep(unsigned long arg, t_data *data)
{
	unsigned long	start_time;

	pthread_mutex_lock(&data->sleep);
	start_time = ft_get_time_of_day();
	while (arg > ft_get_time_of_day() - start_time)
	{
		if (get_lmakla(data) == 0)
		{
			pthread_mutex_unlock(&data->sleep);
			return ;
		}
		usleep(100);
		pthread_mutex_unlock(&data->sleep);
	}
}

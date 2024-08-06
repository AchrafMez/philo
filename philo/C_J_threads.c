/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   C_J_threads.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:18:17 by amezioun          #+#    #+#             */
/*   Updated: 2024/08/05 22:17:18 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = ft_get_time_of_day();
	data->philos->thread = malloc(sizeof(pthread_t *) * data->philo_num);
	if (!data->philos->thread)
		return ;
	while (i < data->philo_num)
	{
		data->philos[i].last_meal_time = data->start_time;
		pthread_create(&data->philos->thread[i], NULL, &routine,
			&data->philos[i]);
		i++;
	}
}

void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		pthread_join(data->philos->thread[i], NULL);
		i++;
	}
}

void	destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		pthread_detach(data->philos->thread[i]);
		i++;
	}
	free(data->philos->thread);
	pthread_mutex_destroy(&data->last_time);
	pthread_mutex_destroy(&data->philos->meal);
	pthread_mutex_destroy(&data->philos->print);
	pthread_mutex_destroy(&data->philos->waiter);
	pthread_mutex_destroy(&data->dead_mut);
	pthread_mutex_destroy(&data->tte);
	pthread_mutex_destroy(&data->sleep);
	pthread_mutex_destroy(&data->lmakla_mut);
	free(data->philos);
	free(data->forks);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:06:09 by amezioun          #+#    #+#             */
/*   Updated: 2024/08/05 22:19:02 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutexes(t_data *data)
{
	int	i;
	int	ret;

	i = 0;
	pthread_mutex_init(&data->last_time, NULL);
	pthread_mutex_init(&data->philos->meal, NULL);
	pthread_mutex_init(&data->philos->print, NULL);
	pthread_mutex_init(&data->philos->waiter, NULL);
	pthread_mutex_init(&data->dead_mut, NULL);
	pthread_mutex_init(&data->tte, NULL);
	pthread_mutex_init(&data->sleep, NULL);
	pthread_mutex_init(&data->lmakla_mut, NULL);
	while (i < data->philo_num)
	{
		ret = pthread_mutex_init(&(data->forks[i].fork), NULL);
		if (ret != 0)
		{
			printf("error in init the mutexes");
			return ;
		}
		i++;
	}
}

int	init(t_data *data)
{
	int	i;

	i = 0;
	data->dead = 0;
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->philo_num);
	if (!data->philos)
		return (1);
	data->forks = malloc(sizeof(t_fork) * data->philo_num);
	if (!data->forks)
		return (1);
	data->lmakla = 0;
	while (i < data->philo_num)
	{
		data->philos[i].philo_id = i + 1;
		data->forks[i].fork_id = i;
		data->philos[i].right_fork = &data->forks[data->philos[i].philo_id - 1];
		data->philos[i].left_fork = &data->forks[i + 1];
		if (i == data->philo_num - 1)
			data->philos[i].left_fork = &data->forks[0];
		data->philos[i].datas = data;
		data->philos[i].numbers_time_to_eat = data->temp;
		i++;
	}
	init_mutexes(data);
	return (0);
}

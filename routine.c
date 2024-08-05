/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:08:17 by amezioun          #+#    #+#             */
/*   Updated: 2024/08/05 23:38:15 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_lmakla(t_data *data)
{
	pthread_mutex_lock(&data->lmakla_mut);
	if (data->args == 6 && data->lmakla > data->philos->numbers_time_to_eat
		* data->philo_num)
	{
		pthread_mutex_unlock(&data->lmakla_mut);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&data->lmakla_mut);
		return (1);
	}
}

void	eat(t_philo *philo)
{
	if (get_dead(philo->datas) == 0)
	{
		pthread_mutex_lock(&philo->print);
		printf("%lu %d is eating\n", ft_get_time_of_day()
			- philo->datas->start_time, philo->philo_id);
		ft_usleep(philo->datas->time_to_eat, philo->datas);
		pthread_mutex_unlock(&philo->print);
		pthread_mutex_lock(&philo->datas->last_time);
		philo->last_meal_time = ft_get_time_of_day();
		pthread_mutex_unlock(&philo->datas->last_time);
		write_on_lmakla(philo->datas);
	}
}

void	thinking(t_philo *philo)
{
	if (get_dead(philo->datas) == 0)
	{
		pthread_mutex_lock(&philo->print);
		printf("%lu %d is thinking\n", ft_get_time_of_day()
			- philo->datas->start_time, philo->philo_id);
		pthread_mutex_unlock(&philo->print);
	}
}

void	sleeping(t_philo *philo)
{
	if (get_dead(philo->datas) == 0)
	{
		pthread_mutex_lock(&philo->print);
		printf("%lu %d is sleeping\n", ft_get_time_of_day()
			- philo->datas->start_time, philo->philo_id);
		ft_usleep(philo->datas->time_to_sleep, philo->datas);
		pthread_mutex_unlock(&philo->print);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if ((get_lmakla(philo->datas) == 0))
		return (NULL);
	if (philo->philo_id % 2 == 0)
		sleeping(philo);
	while (1)
	{
		if ((get_lmakla(philo->datas) == 0))
			return (NULL);
		if ((get_dead(philo->datas)) == 1)
			break ;
		thinking(philo);
		pick_up_forks(philo);
		eat(philo);
		put_down_forks(philo);
		if ((get_lmakla(philo->datas) == 0))
			return (NULL);
		sleeping(philo);
		if ((get_lmakla(philo->datas) == 0))
			return (NULL);
	}
	return (NULL);
}

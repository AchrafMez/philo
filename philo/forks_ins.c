/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:23:25 by amezioun          #+#    #+#             */
/*   Updated: 2024/08/05 22:18:31 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pick_up_forks(t_philo *philo)
{
	if ((pthread_mutex_lock(&(philo->right_fork->fork)) == 0)
		&& (get_dead(philo->datas) == 0))
	{
		pthread_mutex_lock(&philo->print);
		printf("%lu %d has taken a fork\n", ft_get_time_of_day()
			- philo->datas->start_time, philo->philo_id);
		pthread_mutex_unlock(&philo->print);
	}
	if (philo->datas->philo_num == 1)
	{
		ft_usleep(philo->datas->time_to_die, philo->datas);
		return (1);
	}
	else if ((pthread_mutex_lock(&(philo->left_fork->fork)) == 0)
		&& (get_dead(philo->datas)) == 0)
	{
		pthread_mutex_lock(&philo->print);
		printf("%lu %d has taken a fork\n", ft_get_time_of_day()
			- philo->datas->start_time, philo->philo_id);
		pthread_mutex_unlock(&philo->print);
	}
	return (0);
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->right_fork->fork);
	pthread_mutex_unlock(&philo->left_fork->fork);
}

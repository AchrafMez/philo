/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:06:48 by amezioun          #+#    #+#             */
/*   Updated: 2024/08/05 23:24:01 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*arg_check(char *str, t_data *data)
{
	int	minus;
	int	plus;
	int	i;

	minus = 0;
	plus = 0;
	i = 0;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus++;
		else if (str[i] == '+')
			plus++;
		i++;
	}
	if (minus >= 1 || plus > 1)
		data->check_error++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] != '\0' && (!(str[i] >= '0' && str[i] <= '9')))
		data->check_error++;
	return (str);
}

int	treat(char **str, t_data *data)
{
	int	i;

	i = 1;
	data->temp = -1;
	data->check_error = 0;
	while (str[i])
	{
		data->philo_num = ft_atoi(arg_check(str[i++], data));
		data->time_to_die = ft_atoi(arg_check(str[i++], data));
		data->time_to_eat = ft_atoi(arg_check(str[i++], data));
		data->time_to_sleep = ft_atoi(arg_check(str[i++], data));
		if (str[i] != NULL)
			data->temp = ft_atoi(arg_check(str[i++], data));
	}
	if (check_error(data) == 1 || data->check_error >= 1)
		return (1);
	else if (data->check_error == 0)
		return (0);
	return (0);
}

int	ft_atoi(char *str)
{
	int	countminus;
	int	countplus;
	int	number;

	countminus = 0;
	countplus = 0;
	number = 0;
	while (*str == ' ' || *str == '\t' || (*str >= 9 && *str <= 13))
		str++;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			countminus++;
		else if (*str == '+')
			countplus++;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		number = number * 10 + *str - 48;
		str++;
	}
	if (countminus >= 1 || countplus > 1)
		return (0);
	return (number);
}

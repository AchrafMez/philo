/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:06:35 by amezioun          #+#    #+#             */
/*   Updated: 2024/08/05 22:14:39 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		data.args = ac;
		if (treat(av, &data) == 1)
			return (ft_error());
		init(&data);
		create_threads(&data);
		while (1)
		{
			if ((get_lmakla(&data) == 0) || (monitor(&data) == 0))
				break ;
		}
		join_threads(&data);
		destroy(&data);
	}
	else
		ft_error();
	return (0);
}

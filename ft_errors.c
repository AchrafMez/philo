#include "philo.h"

void ft_error(void)
{
    write(2, "Error\n", 6);
    exit(1);
}
void check_error(t_data *data)
{
    if(data->philo_num > 200 || data->philo_num == 0|| data->time_to_die < 60 || data->time_to_eat < 60 || data->time_to_sleep < 60)
        ft_error();
}

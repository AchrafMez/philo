#include "philo.h"

int ft_error(void)
{
    write(2, "Error\n", 6);
    return 1;
}
int check_error(t_data *data)
{
    if(data->philo_num > 200 || data->philo_num == 0|| data->time_to_die < 60 || data->time_to_eat < 60 || data->time_to_sleep < 60 || data->temp == 0)
        return(ft_error());
    else
        return 0;
}

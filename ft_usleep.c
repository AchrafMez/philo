#include "philo.h"

unsigned long ft_get_time_of_day()
{
    unsigned long mili_seconds;
    struct timeval time;
    gettimeofday(&time, NULL);

    mili_seconds = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    return mili_seconds;
}

void ft_usleep(unsigned long arg, t_data *data)
{

    (void) data;
    unsigned long start_time = ft_get_time_of_day();
    while(arg > ft_get_time_of_day() - start_time)
    {
        if(data->args == 6 && data->philo_num * data->philos->numbers_time_to_eat < data->lmakla)
            return ;
        usleep(100);
    }
}

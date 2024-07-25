#include "philo.h"

void ft_arguments_error()
{
    write(2, "Arguments error\n", 16);
    exit(1);
}


// void init(t_data *data)
// {
//     int i = 0;
//     data->philos = malloc(sizeof(*(data->))
//     while(i < data->philo_num)
//     {
//         data->philos[i].philo_id = i + 1;
//         // data->forks[i] = i;
//         i++;
//     }
// }

int main(int ac, char **av)
{
    t_data data;

    if(ac == 5 || ac == 6)
            treat(av, &data);
    // init(&data);
    // data->philos = malloc(sizeof(t_philo) * data->philo_num);
    // if(!data->philo)
    //     return 0;
    printf("number of philo -> %d\n", data.philo_num);
    // printf("number of forks -> %d\n", data.forsk);
    printf("time to die -> %d\n", data.time_to_die);
    printf("time to eat -> %d\n", data.time_to_eat);
    printf("time to sleep -> %d\n", data.time_to_sleep);
    printf("number time to eat -> %d\n", data.numbers_time_to_eat);
    

    int i = 0;
    while(data.philos[i].philo_id)
    {
        printf("philos id ----> %d\n", data.philos[i].philo_id);
        i++;
    }
}
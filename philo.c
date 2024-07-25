#include "philo.h"

void ft_arguments_error(void)
{
    write(2, "Arguments error\n", 16);
    exit(1);
}


 void init(t_data *data)
 {
     int i = 0;
     printf("philo numbers: %d %d\n ", data->philo_num, i);
     while(i < data->philo_num)
     {
         data->philos[i].philo_id = i + 1;
         data->philos[i].right_fork = i;
         data->philos[i].left_fork = i + 1;
             if(i == data->philo_num - 1)
             {
                 data->philos[i].right_fork = i;
                 data->philos[i].left_fork = 0;
             }
         i++;
     }
 }

//:w

int main(int ac, char **av)
{
    t_data data;

    if(ac == 5 || ac == 6)
    {
        treat(av, &data);
        init(&data);

        printf("number of philo -> %d\n", data.philo_num);
        int i = 0;
        while(i < data.philo_num)
        {
            printf("\n===== PHILOS DATA ======\n");
            printf("philos id ----> %d\n", data.philos[i].philo_id);
            printf("right fork %d\n", data.philos[i].right_fork);
            printf("left fork %d\n", data.philos[i].left_fork);
            i++;
        }
//        printf("number of forks -> %d\n", data.forks);
//        printf("time to die -> %d\n", data.time_to_die);
//        printf("time to eat -> %d\n", data.time_to_eat);
//        printf("time to sleep -> %d\n", data.time_to_sleep);
//        printf("number time to eat -> %d\n", data.numbers_time_to_eat);
    }
    else
        ft_error();
    return 0;



}

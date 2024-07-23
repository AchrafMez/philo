#include "philo.h"

void ft_arguments_error()
{
    write(2, "Arguments error\n", 16);
    exit(1);
}



int main(int ac, char **av)
{
    t_philo data;
    if(ac == 5 || ac == 6)
            treat(av, &data);
    else
        return 0;
    printf("number of philo -> %d\n", data.philo);
    printf("number of forks -> %d\n", data.forsk);
    printf("time to die -> %d\n", data.time_to_die);
    printf("time to eat -> %d\n", data.time_to_eat);
    printf("time to sleep -> %d\n", data.time_to_sleep);
    printf("number time to eat -> %d\n", data.numbers_time_to_eat);
}
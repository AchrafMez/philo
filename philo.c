#include "philo.h"

void ft_arguments_error(void)
{
    write(2, "Arguments error\n", 16);
    exit(1);
}


 void init(t_data *data)
 {
     int i = 0;
     data->philos = (t_philo *)malloc(sizeof(t_philo) * data->philo_num);
     if(!data->philos)
            return ;
     data->forks = malloc(sizeof(t_fork) * data->philo_num);
     if(!data->forks)
         return ;
     while(i < data->philo_num)
     {
         data->philos[i].philo_id = i + 1;
         data->forks[i].fork_id = i;
         data->philos[i].right_fork = &data->forks[data->philos[i].philo_id - 1];
         data->philos[i].left_fork = &data->forks[i + 1];
         if (i == data->philo_num - 1)
             data->philos[i].left_fork = &data->forks[0];
         i++;
     }
 }
void pick_up_right_fork()
{

}

void pick_up_left_fork()
{

}

void eat()
{

}

void thinking()
 {
    printf("the philosohpy is thinkg ...\n");
 }

 void* routine()
 {
    thinking();
    int i = 0;
    while(i--)
    {
        printf("");
    }
    return NULL;
 }

 void create_threads(t_data *data)
 {
    int i = 0;
    pthread_t thread1;
    pthread_create(&thread1, NULL, &routine, NULL);

 }


int main(int ac, char **av)
{
    t_data data;

    if(ac == 5 || ac == 6)
    {
        treat(av, &data);
        init(&data);

        int i = 0;
        while(i < data.philo_num) {
            printf("philo id: %d | right fork_id: %d | left fork_id: %d\n", data.philos[i].philo_id,
                   data.philos[i].right_fork->fork_id, data.philos[i].left_fork->fork_id);

            i++;
        }
    }
    else
        ft_error();
    return 0;

}

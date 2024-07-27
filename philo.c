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
     i = 0;
     int ret;
     while(i < data->philo_num)
     {
         ret = pthread_mutex_init(&(data->forks[i].fork), NULL);
         if(ret != 0){
             printf("error in init the mutexes");
             exit(1);
         }
         i++;
     }
 }

void pick_up_forks(t_philo *philo)
{
    pthread_mutex_lock(&philo->waiter);
    if((pthread_mutex_lock(&(philo->right_fork->fork)) == 0) && (pthread_mutex_lock(&(philo->left_fork->fork)) ==0 )){
        printf("the philopher %d pick up right fork %d\n", philo->philo_id , philo->right_fork->fork_id);
        printf("the philopher %d pick up left fork %d\n", philo->philo_id ,philo->left_fork->fork_id);
    } else
    {
        printf("lock mutex failed");
        exit(1);
    }

//    if(pthread_mutex_lock(&(philo->left_fork->fork)) == 0){
//        printf("the philopher %d pick up left fork %d\n", philo->philo_id ,philo->left_fork->fork_id);
//    } else
//    {
//        printf("lock mutex failed");
//        exit(1);
//    }
    pthread_mutex_unlock(&philo->waiter);
}

void put_down_forks(t_philo *philo)
{
    if((pthread_mutex_unlock(&philo->right_fork->fork)) == 0 && (pthread_mutex_unlock(&philo->left_fork->fork)) == 0){
        printf("the philo %d put down right fork %d\n", philo->philo_id, philo->right_fork->fork_id);
        printf("the philo %d put down left fork %d\n", philo->philo_id, philo->left_fork->fork_id);
    }
}

void eat(t_philo *philo)
{
    printf("        the philo %d eating       \n", philo->philo_id);
//    ft_usleep(philo->time_to_eat);
}


void thinking(t_philo *philo)
 {
    printf("the philosopher %d is thinkg \n", philo->philo_id);
 }

 void* routine(void *arg)
 {
    t_philo  *philo = arg;

    if(philo->philo_id % 2 == 0){
        pthread_mutex_lock(&philo->waiter);
        pick_up_forks(philo);
        eat(philo);
        put_down_forks(philo);
//        ft_usleep(philo->time_to_sleep);
        pthread_mutex_unlock(&philo->waiter);
    }
    else
        thinking(philo);
    while (1)
    {
        pick_up_forks(philo);
        eat(philo);
        put_down_forks(philo);
//        ft_usleep(philo->time_to_sleep);
        thinking(philo);
    }



//        eating();
//    printf("philo id in routine : %d\n", philo->philo_id);
    return NULL;
 }

 void create_threads(t_data *data)
 {
    int i = 0;
    data->philos->thread = malloc(sizeof(pthread_t *) * data->philo_num);
    if(!data->philos->thread)
            return ;
    while(i < data->philo_num)
    {
        data->philos[i].time_to_eat = data->time_to_eat;
        data->philos[i].time_to_sleep= data->time_to_sleep;
        pthread_create(&data->philos->thread[i], NULL, &routine, &data->philos[i]);
        printf("time to eat: %d\n", data->philos[i].time_to_eat);
        i++;
    }
//     i = 0;
//     while(i < data->philo_num)
//     {
//         pthread_join(data->philos->thread[i], NULL);
//         i++;
//     }
 }


int main(int ac, char **av)
{
    t_data data;

    if(ac == 5 || ac == 6)
    {
        treat(av, &data);
        init(&data);
        create_threads(&data);
        int i = 0;
//        i = 0;
        while(i < data.philo_num)
        {
            pthread_join(data.philos->thread[i], NULL);
            i++;
        }
//
//        while(i < data.philo_num) {
//            printf("philo id: %d | right fork_id: %d | left fork_id: %d\n", data.philos[i].philo_id,
//                   data.philos[i].right_fork->fork_id, data.philos[i].left_fork->fork_id);
//
//            i++;
//        }
        // u need to add fuction to mnitor the philos
    }
    else
        ft_error();

    return 0;

}

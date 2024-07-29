#include "philo.h"

unsigned  long start_time;
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
         data->philos[i].datas = data;
         i++;
     }

     //init mutexx
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
    if((pthread_mutex_lock(&(philo->right_fork->fork)) == 0)){
        printf("%lu %d has taken a fork\n", ft_get_time_of_day() - start_time, philo->philo_id);
    }
    if(philo->datas->philo_num == 1)
    {
        printf("%lu %d died\n", ft_get_time_of_day() - start_time, philo->philo_id);
        exit(0);
    }
    else if( (pthread_mutex_lock(&(philo->left_fork->fork)) ==0 ))
    {
        printf("%lu %d has taken a fork\n", ft_get_time_of_day() - start_time, philo->philo_id);
    }
    else
    {
        printf("lock mutex failed");
        exit(1);
    }
    pthread_mutex_unlock(&philo->waiter);
}

void put_down_forks(t_philo *philo)
{
    pthread_mutex_lock(&philo->waiter);
    pthread_mutex_unlock(&philo->right_fork->fork);
    pthread_mutex_unlock(&philo->left_fork->fork);
    pthread_mutex_unlock(&philo->waiter);
}

void eat(t_philo *philo)
{
    printf("%lu %d is eating\n", ft_get_time_of_day() - start_time, philo->philo_id);
    ft_usleep(philo->datas->time_to_eat);
    pthread_mutex_lock(&philo->meal);
    philo->last_meal_time = ft_get_time_of_day();
    pthread_mutex_unlock(&philo->meal);
}


void thinking(t_philo *philo)
 {
     printf("%lu %d is thinking\n", ft_get_time_of_day() - start_time, philo->philo_id);
 }

 void sleeping(t_philo *philo)
 {
     printf("%lu %d is sleeping\n", ft_get_time_of_day() - start_time, philo->philo_id);
     ft_usleep(philo->datas->time_to_sleep);
 }

int monitor(t_data *data)
{
    int i = 0;
    unsigned long current_time = ft_get_time_of_day();
    while(i < data->philo_num)
    {
        if(current_time - data->philos[i].last_meal_time > data->time_to_die)
            return 0;
        i++;
    }
    return 1;
}

 void* routine(void *arg)
 {
    t_philo  *philo = arg;

//     printf("time to die: %d\n", philo->datas->time_to_die);
//     printf("time to eat: %d\n", philo->datas->time_to_eat);
//     printf("time to sleep: %d\n", philo->datas->time_to_sleep);
     if (philo->philo_id % 2 == 0)
     {
         thinking(philo);
         ft_usleep(30);
     }
     philo->last_meal_time = ft_get_time_of_day();
     while (1)
     {
         thinking(philo);
         pick_up_forks(philo);
         eat(philo);
         put_down_forks(philo);
        if(monitor(philo->datas) == 0)
        {   
            printf("%lu %d died\n", ft_get_time_of_day() - start_time, philo->philo_id);
            exit(0);
        }
         sleeping(philo);
     }
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
//        data->philos[i].time_to_eat = data->time_to_eat;
//        data->philos[i].time_to_sleep= data->time_to_sleep;
        pthread_create(&data->philos->thread[i], NULL, &routine, &data->philos[i]);
//        printf("time to eat: %d\n", data->philos->datas->time_to_eat);
        i++;
    }
     i = 0;
     while(i < data->philo_num)
     {
         pthread_join(data->philos->thread[i], NULL);
         i++;
     }
 }


int main(int ac, char **av)
{
    t_data data;
    start_time = ft_get_time_of_day();
//    data.philos->start_time = ft_get_time_of_day();
//    printf("philo start: %lu\n", data.philos->start_time);
//    printf("data start :%lu\n", data.start_time);
//    unsigned long start = ft_get_time_of_day();
//    printf("start -> %lu", ft_get_time_of_day() - start);

//    exit(0);
    if(ac == 5 || ac == 6)
    {
        treat(av, &data);
        init(&data);
        create_threads(&data);
        printf("%ld\n", data.philos[0].last_meal_time);
        sleep(10);
//        int i = 0;
//        while(i < data.philo_num)
//        {
//            pthread_join(data.philos->thread[i], NULL);
//            i++;
//        }
        // u need to add fuction to mnitor the philos
    }
    else
        ft_error();

    return 0;
//        int i = 0;
//            while(i < data.philo_num) {
//    //            printf("philo id: %d | right fork_id: %d | left fork_id: %d\n", data.philos[i].philo_id,
//    //                   data.philos[i].right_fork->fork_id, data.philos[i].left_fork->fork_id);
//    //
//                printf("philo %d: | time to stleep %d : \n",data.philos[i].philo_id, data.philos[i].datas->time_to_sleep);
//                printf("philo %d: | time to eat %d : \n", data.philos[i].philo_id, data.philos[i].datas->time_to_eat);
//                printf("philo: %d | time to die:  %d\n", data.philos[i].philo_id, data.philos[i].datas->time_to_die);
//                usleep(200000);
//                i++;
//            }

}

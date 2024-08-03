#include "philo.h"

void ft_arguments_error(void)
{
    write(2, "Arguments error\n", 16);
    exit(1);
}

int nttoeat;
 void init(t_data *data)
 {
     int i = 0;
     data->philos = (t_philo *)malloc(sizeof(t_philo) * data->philo_num);
     if(!data->philos)
            return ;
     data->forks = malloc(sizeof(t_fork) * data->philo_num);
     if(!data->forks)
         return ;
     data->lmakla = 0;
     data->count = 0;
     while(i < data->philo_num)
     {
         data->philos[i].philo_id = i + 1;
         data->forks[i].fork_id = i;
         data->philos[i].right_fork = &data->forks[data->philos[i].philo_id - 1];
         data->philos[i].left_fork = &data->forks[i + 1];
         if (i == data->philo_num - 1)
             data->philos[i].left_fork = &data->forks[0];
         data->philos[i].datas = data;
         data->philos[i].numbers_time_to_eat = data->temp;
         i++;
     }

     //init mutexx
     i = 0;
     pthread_mutex_init(&data->philos->print, NULL);
     pthread_mutex_init(&data->philos->waiter, NULL);
     pthread_mutex_init(&data->last_time, NULL);
     pthread_mutex_init(&data->dead_mut, NULL);
     pthread_mutex_init(&data->tte, NULL);
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
int get_dead(t_data *data)
{
    //1 dead
    //0 not dead
    int is_die;
    pthread_mutex_lock(&data->dead_mut);
    is_die = data->dead;
    pthread_mutex_unlock(&data->dead_mut);
    return(is_die);
}

int pick_up_forks(t_philo *philo)
{
    if((pthread_mutex_lock(&(philo->right_fork->fork)) == 0) && (get_dead(philo->datas) == 0)){
        printf("%lu %d has taken a fork\n", ft_get_time_of_day() - philo->datas->start_time, philo->philo_id);
    }
    if(philo->datas->philo_num == 1)
    {
        ft_usleep(philo->datas->time_to_die, philo->datas);
        printf("%lu %d died\n", ft_get_time_of_day() - philo->datas->start_time, philo->philo_id);
        return 1;
    }
    else if( (pthread_mutex_lock(&(philo->left_fork->fork)) == 0) && (get_dead(philo->datas)) == 0)
    {
        printf("%lu %d has taken a fork\n", ft_get_time_of_day() - philo->datas->start_time, philo->philo_id);
    }
//    else
//    {
//        printf("lock mutex failed");
//        return (1);
//    }
    return 0;
}

void put_down_forks(t_philo *philo)
{
    pthread_mutex_unlock(&philo->right_fork->fork);
    pthread_mutex_unlock(&philo->left_fork->fork);
}


void eat(t_philo *philo)
{
     if(get_dead(philo->datas) == 0)
     {

        pthread_mutex_lock(&philo->print);
        printf("%lu %d is eating\n", ft_get_time_of_day() - philo->datas->start_time, philo->philo_id);
        ft_usleep(philo->datas->time_to_eat, philo->datas);
        pthread_mutex_lock(&philo->datas->last_time);
        philo->last_meal_time = ft_get_time_of_day();
        pthread_mutex_lock(&philo->datas->tte);
        philo->datas->lmakla++;
        pthread_mutex_unlock(&philo->datas->last_time);
        pthread_mutex_unlock(&philo->datas->tte);
        pthread_mutex_unlock(&philo->print);
     }
}

void thinking(t_philo *philo)
 {
    if(get_dead(philo->datas) == 0)
    {
         pthread_mutex_lock(&philo->print);
         printf("%lu %d is thinking\n", ft_get_time_of_day() - philo->datas->start_time, philo->philo_id);
         pthread_mutex_unlock(&philo->print);
    }
 }

 void sleeping(t_philo *philo)
 {
    if(get_dead(philo->datas) == 0)
    {

         pthread_mutex_lock(&philo->print);
         printf("%lu %d is sleeping\n", ft_get_time_of_day() - philo->datas->start_time, philo->philo_id);
         ft_usleep(philo->datas->time_to_sleep, philo->datas);
         pthread_mutex_unlock(&philo->print);
    }
 }
int get_tte(t_philo *philo)
{
     int tte;
     pthread_mutex_lock(&philo->datas->tte);
     tte = philo->numbers_time_to_eat;
     pthread_mutex_unlock(&philo->datas->tte);
     return tte;
}

// int count_meals_eaten(t_data *data)
// {
//        pthread_mutex_lock(&data->tte);
//        if()
//        {
////            printf("philo id %d count meals function ---> %d\n",data->philos[i].philo_id, data->philos[i].numbers_time_to_eat);
//            return 1;
//        }
//        else
////            data->philos[i].numbers_time_to_eat--;
//        pthread_mutex_unlock(&data->tte);
//    return 0;
// }

int monitor(t_data *data)
{
    int i = 0;
    unsigned long last_meal_t;
    while(i < data->philo_num)
    {
            if(data->args == 6 && data->lmakla > data->philos->numbers_time_to_eat * data->philo_num)
            {
                return 2;
            }
            pthread_mutex_lock(&data->last_time);
            last_meal_t = data->philos[i].last_meal_time;
            pthread_mutex_unlock(&data->last_time);
            if(ft_get_time_of_day() - last_meal_t >= data->time_to_die )
            {
//                printf("%d");
                data->dead = 1;
                printf("%lu %d died\n", ft_get_time_of_day() - data->start_time, data->philos[i].philo_id);
                return  0;
            }
        i++;
    }
    return 1;
}

 void* routine(void *arg)
 {
    t_philo  *philo = arg;

     if(philo->datas->args == 6 && philo->datas->lmakla > philo->numbers_time_to_eat * philo->datas->philo_num)
     {
         return NULL ;
     }
     if (philo->philo_id % 2 == 0)
         sleeping(philo);
     while (1)
     {

         if(philo->datas->args == 6 && philo->datas->lmakla > philo->numbers_time_to_eat * philo->datas->philo_num)
         {
             return NULL ;
         }
         if((get_dead(philo->datas)) == 1)
         {
//             printf("n time to eat in routine -> %d\n", philo->datas->philos->numbers_time_to_eat);
             break ;
         }
         thinking(philo);
         pick_up_forks(philo);
         eat(philo);
         put_down_forks(philo);
         if(philo->datas->args == 6 && philo->datas->lmakla > philo->numbers_time_to_eat * philo->datas->philo_num)
         {
             return NULL ;
         }
         sleeping(philo);
         if(philo->datas->args == 6 && philo->datas->lmakla > philo->numbers_time_to_eat * philo->datas->philo_num)
         {
             return NULL ;
         }
     }
    return NULL;
 }
 void create_threads(t_data *data)
 {
    int i = 0;
    data->start_time = ft_get_time_of_day();
    data->philos->thread = malloc(sizeof(pthread_t *) * data->philo_num);
    if(!data->philos->thread)
            return ;
     while(i < data->philo_num)
    {
         data->philos[i].last_meal_time = data->start_time;
        pthread_create(&data->philos->thread[i], NULL, &routine, &data->philos[i]);
        i++;
    }
 }


int main(int ac, char **av)
{
    t_data data;
    data.dead = 0;
    if(ac == 5 || ac == 6)
    {
        data.args = ac;
        treat(av, &data);
        init(&data);
//        int i = 0;
//        while(i < data.philo_num)
//        {
//            printf("%d   time to eat -> %d\n",data.philos[i].philo_id, data.philos[i].numbers_time_to_eat);
//            i++;
//        }
//        return 0;
//        printf("ntto eat -> %d\n", data.philos->numbers_time_to_eat);
//        printf(" lmakla -> %d\n", data.lmakla);
        create_threads(&data);
        while(1)
        {
            if((data.args == 6  && data.lmakla > data.philo_num * data.philos->numbers_time_to_eat) || (monitor(&data) == 0))
            {
//                printf("%d\n", data.lmakla);
                break ;
            }
        }

        int j = 0;
        while(j < data.philo_num)
        {
            pthread_join(data.philos->thread[j], NULL);
            j++;
        }
    }
    else
        ft_error();
    return 0;
}

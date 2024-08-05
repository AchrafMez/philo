#include "philo.h"

void ft_arguments_error(void)
{
    write(2, "Arguments error\n", 16);
    exit(1);
}

 int init(t_data *data)
 {
     int i = 0;
     data->philos = (t_philo *)malloc(sizeof(t_philo) * data->philo_num);
     if(!data->philos)
            return 1;
     data->forks = malloc(sizeof(t_fork) * data->philo_num);
     if(!data->forks)
         return 1;
     data->lmakla = 0;
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
     pthread_mutex_init(&data->last_time, NULL);
     pthread_mutex_init(&data->philos->meal, NULL);
     pthread_mutex_init(&data->philos->print, NULL);
     pthread_mutex_init(&data->philos->waiter, NULL);
     pthread_mutex_init(&data->dead_mut, NULL);
     pthread_mutex_init(&data->tte, NULL);
     pthread_mutex_init(&data->sleep, NULL);
     pthread_mutex_init(&data->lmakla_mut, NULL);
     int ret;
     while(i < data->philo_num)
     {
         ret = pthread_mutex_init(&(data->forks[i].fork), NULL);
         if(ret != 0){
             printf("error in init the mutexes");
             return 1;
         }
         i++;
     }
     return 0;
 }

 void destroy(t_data *data)
 {
     int i = 0;
     while(i < data->philo_num)
     {
         pthread_detach(data->philos->thread[i]);
         i++;
     }
     free(data->philos->thread);
     pthread_mutex_destroy(&data->last_time);
     pthread_mutex_destroy(&data->philos->meal);
     pthread_mutex_destroy(&data->philos->print);
     pthread_mutex_destroy(&data->philos->waiter);
     pthread_mutex_destroy(&data->dead_mut);
     pthread_mutex_destroy(&data->tte);
     pthread_mutex_destroy(&data->sleep);
     pthread_mutex_destroy(&data->lmakla_mut);
     free(data->philos);
     free(data->forks);
 }

int get_dead(t_data *data)
{
    pthread_mutex_lock(&data->dead_mut);
    int is_die = data->dead;
    pthread_mutex_unlock(&data->dead_mut);
    return(is_die);
}

int pick_up_forks(t_philo *philo)
{
    if((pthread_mutex_lock(&(philo->right_fork->fork)) == 0) && (get_dead(philo->datas) == 0)){
        pthread_mutex_lock(&philo->print);
        printf("%lu %d has taken a fork\n", ft_get_time_of_day() - philo->datas->start_time, philo->philo_id);
        pthread_mutex_unlock(&philo->print);
    }
    if(philo->datas->philo_num == 1)
    {
        ft_usleep(philo->datas->time_to_die, philo->datas);
        return 1;
    }
    else if( (pthread_mutex_lock(&(philo->left_fork->fork)) == 0) && (get_dead(philo->datas)) == 0)
    {
        pthread_mutex_lock(&philo->print);
        printf("%lu %d has taken a fork\n", ft_get_time_of_day() - philo->datas->start_time, philo->philo_id);
        pthread_mutex_unlock(&philo->print);
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

void write_on_lmakla(t_data *data)
{
    pthread_mutex_lock(&data->lmakla_mut);
    data->lmakla++;
    pthread_mutex_unlock(&data->lmakla_mut);
}
void eat(t_philo *philo)
{
     if(get_dead(philo->datas) == 0)
     {

        pthread_mutex_lock(&philo->print);
        printf("%lu %d is eating\n", ft_get_time_of_day() - philo->datas->start_time, philo->philo_id);
        ft_usleep(philo->datas->time_to_eat, philo->datas);
        pthread_mutex_unlock(&philo->print);
        pthread_mutex_lock(&philo->datas->last_time);
        philo->last_meal_time = ft_get_time_of_day();
        pthread_mutex_unlock(&philo->datas->last_time);
         write_on_lmakla(philo->datas);
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

int get_lmakla(t_data *data)
{
     pthread_mutex_lock(&data->lmakla_mut);
     if(data->args == 6 && data->lmakla > data->philos->numbers_time_to_eat * data->philo_num)
     {
         pthread_mutex_unlock(&data->lmakla_mut);
         return 0;
     }
     else
     {
        pthread_mutex_unlock(&data->lmakla_mut);
         return 1;
     }
}
int monitor(t_data *data)
{
    int i = 0;
    unsigned long last_meal_t;
    while(i < data->philo_num)
    {
            if((get_lmakla(data) == 0))
            {
                return 2;
            }
            pthread_mutex_lock(&data->last_time);
            last_meal_t = data->philos[i].last_meal_time;
            pthread_mutex_unlock(&data->last_time);
            if(ft_get_time_of_day() - last_meal_t >= data->time_to_die )
            {
                pthread_mutex_lock(&data->dead_mut);
                data->dead = 1;
                printf("%lu %d died\n", ft_get_time_of_day() - data->start_time, data->philos[i].philo_id);
                pthread_mutex_unlock(&data->dead_mut);
                return  0;
            }
        i++;
    }
    return 1;
}

 void* routine(void *arg)
 {
    t_philo  *philo = arg;
     if((get_lmakla(philo->datas) == 0))
         return NULL ;
     if (philo->philo_id % 2 == 0)
         sleeping(philo);
     while (1)
     {
         if((get_lmakla(philo->datas) == 0))
             return NULL ;
         if((get_dead(philo->datas)) == 1)
             break ;
         thinking(philo);
         pick_up_forks(philo);
         eat(philo);
         put_down_forks(philo);
         if((get_lmakla(philo->datas) == 0))
             return NULL ;
         sleeping(philo);
         if((get_lmakla(philo->datas) == 0))
             return NULL ;
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

void test()
{
     system("leaks philo ");
}

int main(int ac, char **av)
{
    t_data data;

    atexit(test);
    data.dead = 0;
    if(ac == 5 || ac == 6)
    {
        data.args = ac;
        if(treat(av, &data) == 1)
            return ft_error();
        init(&data);
        create_threads(&data);
        while(1)
        {
            if ((get_lmakla(&data) == 0) || (monitor(&data) == 0))
                break ;
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
    destroy(&data);
    return 0;
}

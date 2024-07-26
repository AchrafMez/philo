//void init(t_data *data)
//{
//    int i = 0;
//    data->philos = (t_philo *)malloc(sizeof(t_philo) * data->philo_num);
//    if(!data->philos)
//        return ;
//    data->forks = malloc(sizeof(t_fork) * data->philo_num);
//    if(!data->forks)
//        return ;
//    while(i < data->philo_num)
//    {
//        data->philos[i].philo_id = i + 1;
//        data->forks[i].fork_id = i;
//        data->philos[i].right_fork = &data->forks[data->philos[i].philo_id - 1];
//        data->philos[i].left_fork = &data->forks[data->philos[i].philo_id];
//        if (i == data->philo_num - 1)
//            data->philos[i].left_fork = &data->forks[0];
//        i++;
//    }
//}

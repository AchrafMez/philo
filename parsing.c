#include "philo.h"

char* arg_check(char *str)
{
    int minus = 0;
    int plus = 0;
    int i = 0;
    while(str[i] == '-' || str[i] == '+')
    {
        if(str[i] == '-')
            minus++;
        else if(str[i] == '+')
            plus++;
        i++;
    }
    if(minus >= 1 || plus > 1)
        ft_arguments_error();
    while(str[i] >= '0' && str[i] <= '9')
        i++;
    if((str[i] != '\0') && (!(str[i] >= '0' && str[i] <= '9')))
        ft_arguments_error();
    return str;
}

void treat(char **str, t_data *data)
{
    int i = 1;
    data->numbers_time_to_eat = -1;
    while(str[i])
    {
        data->philo_num = ft_atoi(arg_check(str[i++]));
        data->time_to_die = ft_atoi(arg_check(str[i++]));
        data->time_to_eat = ft_atoi(arg_check(str[i++]));
        data->time_to_sleep = ft_atoi(arg_check(str[i++]));
        if(str[i] != NULL)
            data->numbers_time_to_eat = ft_atoi(arg_check(str[i++]));
    }
    check_error(data);
}

int ft_atoi(char *str)
{
    int countminus = 0;
    int countplus = 0;
    int number = 0;

    while(*str == ' ' || *str == '\t' || (*str >= 9 && *str <= 13))
        str++;
    while(*str == '-' || *str == '+')
    {
        if(*str == '-')
            countminus++;
        else if(*str == '+')
            countplus++;
        str++;
    }
    while(*str >= '0' && *str <= '9')
    {
        number = number * 10 + *str - 48;
        str++;
    }
    if(countminus >= 1 || countplus > 1)
        return 0;
    else
        return number;        
}

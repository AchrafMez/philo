#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>


typedef struct s_philo
{
    unsigned int philo;
    unsigned int forsk;
    unsigned int time_to_die;
    unsigned int time_to_eat;
    unsigned int time_to_sleep;
    unsigned int numbers_time_to_eat;
}   t_philo;

//parsing
char *arg_check(char *str);
void treat(char **str, t_philo *data);
int ft_atoi(char *str);
void ft_arguments_error();
#endif
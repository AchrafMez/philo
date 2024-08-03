#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_data t_data;

typedef struct s_fork
{
    pthread_mutex_t fork;
    int fork_id;
} t_fork;

typedef struct s_philo
{
    pthread_t *thread;
    pthread_mutex_t waiter;
    pthread_mutex_t meal;
    pthread_mutex_t print;
    int philo_id;
    t_fork *left_fork;
    t_fork *right_fork;
    t_data *datas;
    unsigned long last_meal_time;
    int numbers_time_to_eat;
}   t_philo;

typedef struct s_data
{
    t_philo *philos;
    t_fork *forks;
    unsigned long sleep;
    pthread_mutex_t last_time;
    int args;
    unsigned int time_to_die;
    unsigned int time_to_eat;
    unsigned int time_to_sleep;
    int temp;
    int philo_num;
    pthread_mutex_t dead_mut;
    pthread_mutex_t tte;
    int dead;
    unsigned long start_time;
    int lmakla;
    int count;
} t_data;


/*
    create a struct that wold contain general information 
    when did the simulation start
    arr philos
    arr forks
*/

/*
    pthread_create
    pthread_join
    pthread_detash
    pthread_mutex_lock
    pthread_mutex_unlock
*/

// 200 Philos :  array of structs 200 philos
// usleep custom made for sleeping in ms getcurrenttime()
// 200 Forks :  Initialize array  of 200 forks of type pthead_mutex_t

/*   ROUTINE CONDITIONS       */
    /*
        1. PHILO HAS DIED
        2. PHILO HAS REACHED ITS LIMIT == TIMES_EATEN == 0
    */

// Ittereate through philosephers
    // Fill information for each philo
    // Itterate through each philosephers giving it the fuction routine
        // should put to sleep the even philos
        // The odd should start the routine
            // need to lock his fork with othread_mutex_lock
                //printf has taken a fork
            // lock the fork next to him
            // start eating (printf statring to eat)
                //suspend program by time to eat
                // update last_eaten
                // update philo_times eaten
                        // philo->times_eaten--;
                // unlock the forks 
                // put the philo to slee;
// variable so that all philos have access to it 
// once this variablr turn true then no other thread can run the routine 
// so we should return to the main function 

// Create a monitoring function : 
    // itterate through each philo 
     // check is current_time - lasteaten < time to die
     // a philo has died 
            //  lock the printf mutex so that no ither thread can run printf
            // kill all philosephers
//errors
void ft_error(void);
void check_error(t_data *data);

//parsing
char *arg_check(char *str);
void treat(char **str, t_data *data);
int ft_atoi(char *str);
void ft_arguments_error(void);

//usleep
void ft_usleep(unsigned long arg, t_data *data);
unsigned long ft_get_time_of_day();

#endif
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



//parsing
char *arg_check(char *str);
void treat(char **str, t_philo *data);
int ft_atoi(char *str);
void ft_arguments_error();
#endif
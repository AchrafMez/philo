/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:06:12 by amezioun          #+#    #+#             */
/*   Updated: 2024/08/05 23:49:57 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_fork
{
	pthread_mutex_t		fork;
	int					fork_id;
}						t_fork;

typedef struct s_philo
{
	pthread_t			*thread;
	pthread_mutex_t		waiter;
	pthread_mutex_t		meal;
	pthread_mutex_t		print;
	int					philo_id;
	t_fork				*left_fork;
	t_fork				*right_fork;
	t_data				*datas;
	unsigned long		last_meal_time;
	int					numbers_time_to_eat;
}						t_philo;

typedef struct s_data
{
	t_philo				*philos;
	t_fork				*forks;
	pthread_mutex_t		sleep;
	pthread_mutex_t		last_time;
	pthread_mutex_t		dead_mut;
	pthread_mutex_t		tte;
	int					args;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	int					temp;
	int					philo_num;
	int					dead;
	unsigned long		start_time;
	pthread_mutex_t		lmakla_mut;
	int					lmakla;
	int					check_error;
}						t_data;

//errors
int						ft_error(void);
int						check_error(t_data *data);

//parsing
char					*arg_check(char *str, t_data *data);
int						treat(char **str, t_data *data);
int						ft_atoi(char *str);
void					ft_arguments_error(void);

//usleep
void					ft_usleep(unsigned long arg, t_data *data);
unsigned long			ft_get_time_of_day(void);

//
int						get_lmakla(t_data *data);

//routine
int						get_lmakla(t_data *data);
void					eat(t_philo *philo);
void					thinking(t_philo *philo);
void					sleeping(t_philo *philo);
void					*routine(void *arg);

//init
void					init_mutexes(t_data *data);
int						init(t_data *data);

//monitor
void					write_on_lmakla(t_data *data);
int						get_dead(t_data *data);
int						monitor(t_data *data);

//forsk instruction
int						pick_up_forks(t_philo *philo);
void					put_down_forks(t_philo *philo);

//cj_threads
void					create_threads(t_data *data);
void					join_threads(t_data *data);
void					destroy(t_data *data);

#endif
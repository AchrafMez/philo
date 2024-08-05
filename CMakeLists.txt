cmake_minimum_required(VERSION 3.15)
project(phiiiiilloooo C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(phiiiiilloooo
        test/testing.c
        error_func.c
        ft_errors.c
        ft_usleep.c
        parsing.c
        philo.c
        philo.h)

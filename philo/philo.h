/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 10:36:01 by abazerou          #+#    #+#             */
/*   Updated: 2023/06/26 18:05:38 by abazerou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>




typedef struct t_param
{
    int philo_num;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat_num;
}t_param;

typedef struct t_philo
{
    int id;
    int meals_n;
    int is_dead;
    long last_meal_time;
    long time_since_last_meal;
    pthread_mutex_t fork;
    pthread_mutex_t death_mutex;
    pthread_t thread;
    struct t_philo *next;
    struct t_param *par;
    struct timeval start_time;
    long time;
}t_philo;



void	ft_puterror(char *s);
void	ft_putstr_fd(char *s, int fd);
int     ft_isdigit(int c);
long get_time(void);
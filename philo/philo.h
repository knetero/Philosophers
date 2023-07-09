/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 10:36:01 by abazerou          #+#    #+#             */
/*   Updated: 2023/07/09 19:20:59 by abazerou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <time.h> 
# include <sys/time.h>

typedef struct t_param
{
	struct t_philo	*philo;
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_num;
}t_param;

typedef struct t_philo
{
	int				id;
	int				meals_n;
	struct t_philo	*next;
	struct t_param	*par;
	struct t_data	*data;
	time_t			last_meal_t;
	time_t			time_since_last_meal;
	pthread_mutex_t	fork;
	pthread_t		thread;
}t_philo;

typedef struct t_data
{
	time_t			time;
	int				dead;
	struct timeval	start_time;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
}t_data;

int					ft_atoi(const char *str);
int					ft_isdigit(int c);
int					check_death(t_philo *philo, int ac);
int					check_eat(t_philo *philo, int eat);
int					start_threads(t_param *par, t_philo *philo, int ac);
int					check_death_2(t_philo *p, int i);
void				ft_putstr_fd(char *s, int fd);
int					check_values(char **av, int ac);
void				ft_usleep(time_t time);
void				param_init(char **av, int ac, t_param *table);
void				*routine(void *arg);
void				print_ac(char *s, int id, t_philo *philo);
t_philo				*ft_make_philo(t_param *p, t_data *data);
time_t				get_time(time_t start_time);
time_t				get_time(time_t start_time);
t_philo				*create_philo(t_param *p, t_data *data, int i);
time_t				start_time(t_data *data);

#endif
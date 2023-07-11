/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:51:30 by abazerou          #+#    #+#             */
/*   Updated: 2023/07/11 22:24:31 by abazerou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_eat(t_philo *philo, int ac)
{
	int	i;
	int	eat_num;

	if (ac == 6)
	{
		eat_num = 0;
		i = 1;
		while (i <= philo->par->philo_num)
		{
			pthread_mutex_lock(&philo->data->meals_mutex);
			if (philo->meals_n >= philo->par->must_eat_num)
				eat_num++;
			pthread_mutex_unlock(&philo->data->meals_mutex);
			philo = philo->next;
			i++;
		}
		if (eat_num == philo->par->philo_num)
			return (1);
	}
	return (0);
}

int	check_death(t_philo *p, int ac)
{
	int	i;

	if (check_eat(p, ac) == 1)
		return (1);
	i = 1;
	while (i <= p->par->philo_num)
	{
		pthread_mutex_lock(&p->data->last_meal_mutex);
		if (get_time(p->data->time) - p->last_meal_t >= p->par->time_to_die)
		{
			pthread_mutex_lock(&p->data->print_mutex);
			printf("%ld %d is dead\n", get_time(p->data->time), p->id);
			usleep(2000);
			return (1);
		}
		pthread_mutex_unlock(&p->data->last_meal_mutex);
		p = p->next;
		i++;
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		usleep(200);
	while (1)
	{
		pthread_mutex_lock(&philo->fork);
		print_ac("has taken a fork\n", philo->id, philo);
		pthread_mutex_lock(&philo->next->fork);
		print_ac("has taken a fork\n", philo->id, philo);
		pthread_mutex_lock(&philo->data->last_meal_mutex);
		philo->last_meal_t = get_time(philo->data->time);
		pthread_mutex_unlock(&philo->data->last_meal_mutex);
		print_ac("is eating\n", philo->id, philo);
		pthread_mutex_lock(&philo->data->meals_mutex);
		philo->meals_n++;
		pthread_mutex_unlock(&philo->data->meals_mutex);
		ft_usleep(philo->par->time_to_eat);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		print_ac("is sleeping\n", philo->id, philo);
		ft_usleep(philo->par->time_to_sleep);
		print_ac("is thinking\n", philo->id, philo);
	}
}

int	start_threads(t_philo *philo)
{
	int	i;

	i = 1;
	while (i <= philo->par->philo_num)
	{
		if (pthread_create(&philo->thread, NULL, &routine, philo) != 0)
			return (printf("[ERROR] : FAILED TO CREAT THREAD\n"), 1);
		philo = philo->next;
		i++;
	}
	i = 1;
	while (i <= philo->par->philo_num)
	{
		if (pthread_detach(philo->thread) != 0)
			return (printf("[ERROR] : FAILED TO DETACH\n"), 1);
		philo = philo->next;
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:51:30 by abazerou          #+#    #+#             */
/*   Updated: 2023/07/12 17:22:06 by abazerou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_eat(t_philo *philo)
{
	int	i;
	int	eat_num;

	i = 1;
	eat_num = 0;
	while (i <= philo->par->philo_num)
	{
		pthread_mutex_lock(&philo->meals_mutex);
		if (philo->meals_n >= philo->par->must_eat_num)
			eat_num++;
		pthread_mutex_unlock(&philo->meals_mutex);
		philo = philo->next;
		i++;
	}
	if (eat_num == philo->par->philo_num)
		return (1);
	return (0);
}

void	philo_dead(t_philo *p)
{
	int	j;

	j = 0;
	while (j < p->par->philo_num)
	{
		pthread_mutex_lock(&p->dead_mutex);
		p->dead = 1;
		pthread_mutex_unlock(&p->dead_mutex);
		p = p->next;
		j++;
	}
}

int	check_death(t_philo *p, int ac)
{
	int	i;

	if (ac == 6)
	{
		if (check_eat(p) == 1)
			return (1);
	}
	i = 0;
	while (++i <= p->par->philo_num)
	{
		pthread_mutex_lock(&p->last_meal_mutex);
		if (get_time(p->data->time) - p->last_meal_t >= p->par->time_to_die)
		{
			philo_dead(p);
			pthread_mutex_lock(&p->par->print_mutex);
			printf("%ld %d is dead\n", get_time(p->data->time), p->id);
			return (1);
		}
		pthread_mutex_unlock(&p->last_meal_mutex);
		p = p->next;
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(200);
	while (1)
	{
		pthread_mutex_lock(&philo->fork);
		print_ac("has taken a fork\n", philo->id, philo);
		pthread_mutex_lock(&philo->next->fork);
		print_ac("has taken a fork\n", philo->id, philo);
		pthread_mutex_lock(&philo->last_meal_mutex);
		philo->last_meal_t = get_time(philo->data->time);
		pthread_mutex_unlock(&philo->last_meal_mutex);
		print_ac("is eating\n", philo->id, philo);
		meals_counter(philo);
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

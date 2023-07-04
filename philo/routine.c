/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:51:30 by abazerou          #+#    #+#             */
/*   Updated: 2023/07/04 18:06:25 by abazerou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_eat(t_philo *philo, int eat)
{
	t_philo	*tmp;
	int		i;

	tmp = philo;
	i = 1;
	while (i <= tmp->par->philo_num)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		if (tmp->meals_n >= tmp->par->must_eat_num)
			eat++;
		pthread_mutex_unlock(&philo->data->death_mutex);
		tmp = tmp->next;
		i++;
	}
	if (eat == tmp->par->philo_num)
		return (1);
	return (0);
}

int	check_death_2(t_philo *p, int i)
{
	while (++i <= p->par->philo_num)
	{
		pthread_mutex_lock(&p->data->death_mutex);
		if (get_time(p->data->time) - p->last_meal_t >= p->par->time_to_die)
		{
			pthread_mutex_lock(&p->data->print_mutex);
			printf("%ld %d is dead.\n", get_time(p->data->time), p->id);
			return (usleep(1000), 1);
		}
		pthread_mutex_unlock(&p->data->death_mutex);
		p = p->next;
	}
	return (0);
}

int	check_death(t_philo *p, int ac)
{
	int	i;
	int	eat;

	while (1)
	{
		eat = 0;
		if (ac == 6)
		{
			if (check_eat(p, eat) == 1)
				return (1);
		}
		i = 0;
		if (check_death_2(p, i) == 1)
			return (1);
		usleep(200);
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
		pthread_mutex_lock(&(philo->fork));
		print_ac("has taken a fork \n", philo->id, philo);
		pthread_mutex_lock(&(philo->next->fork));
		print_ac("has taken a fork\n", philo->id, philo);
		print_ac("is eating\n", philo->id, philo);
		pthread_mutex_lock(&philo->data->death_mutex);
		philo->last_meal_t = get_time(philo->data->time);
		philo->meals_n++;
		pthread_mutex_unlock(&philo->data->death_mutex);
		ft_usleep(philo->par->time_to_eat);
		pthread_mutex_unlock(&(philo->next->fork));
		pthread_mutex_unlock(&(philo->fork));
		print_ac("is sleeping\n", philo->id, philo);
		ft_usleep(philo->par->time_to_sleep);
		print_ac("is thinking\n", philo->id, philo);
	}
	return (NULL);
}

void	start_threads(t_param *par, t_philo *philo, int ac)
{
	int	i;

	i = 1;
	while (i <= par->philo_num)
	{
		if (pthread_create(&philo->thread, NULL, &routine, philo) != 0)
			ft_puterror("[Error]: failed to create thread!\n");
		philo = philo->next;
		i++;
	}
	i = 1;
	while (i <= par->philo_num)
	{
		if (pthread_detach(philo->thread) != 0)
			ft_puterror("error\n");
		philo = philo->next;
		i++;
	}
	while (1)
	{
		check_death(philo, ac);
		break ;
	}
}

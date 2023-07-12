/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 10:46:00 by abazerou          #+#    #+#             */
/*   Updated: 2023/07/12 20:50:48 by abazerou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	meals_counter(t_philo *philo)
{
	pthread_mutex_lock(&philo->meals_mutex);
	philo->meals_n++;
	pthread_mutex_unlock(&philo->meals_mutex);
}

void	print_ac(char *s, int id, t_philo *philo)
{
	pthread_mutex_lock(&philo->dead_mutex);
	if (philo->dead == 0)
	{
		pthread_mutex_lock(&philo->par->print_mutex);
		printf("%ld %d %s", get_time(philo->data->time), id, s);
		pthread_mutex_unlock(&philo->par->print_mutex);
	}
	pthread_mutex_unlock(&philo->dead_mutex);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	result;

	result = 0;
	i = 0;
	if (ft_strlen(str) == 0)
		return (-1);
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
	{
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (!ft_isdigit(str[i]) && str[i])
		return (-1);
	return (result);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

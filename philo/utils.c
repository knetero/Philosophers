/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 10:46:00 by abazerou          #+#    #+#             */
/*   Updated: 2023/07/09 21:02:15 by abazerou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_ac(char *s, int id, t_philo *philo)
{
	if(philo->data->dead != 0)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%ld %d %s", get_time(philo->data->time), id, s);
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
	return;
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
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (!ft_isdigit(str[i]) && str[i])
		return(-1);
	return (result);
}

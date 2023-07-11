/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:14:17 by abazerou          #+#    #+#             */
/*   Updated: 2023/07/11 18:55:44 by abazerou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	start_time(t_data *d)
{
	time_t	start;

	pthread_mutex_init(&d->print_mutex, NULL);
	pthread_mutex_init(&d->death_mutex, NULL);
	pthread_mutex_init(&d->meals_mutex, NULL);
	gettimeofday(&d->start_time, NULL);
	start = (d->start_time.tv_sec * 1000) + (d->start_time.tv_usec / 1000);
	return (start);
}

void	ft_usleep(time_t time)
{
	time_t			current_time;
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	current_time = start_time.tv_sec * 1000 + start_time.tv_usec / 1000;
	while ((get_time(current_time)) < time)
		usleep(80);
}

time_t	get_time(time_t start_time)
{
	struct timeval	current_time;
	time_t			time;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time - start_time);
}

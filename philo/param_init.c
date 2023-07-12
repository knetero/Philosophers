/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:13:17 by abazerou          #+#    #+#             */
/*   Updated: 2023/07/12 16:58:04 by abazerou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_make_philo(t_param *p, t_data *data)
{
	t_philo	*head;
	t_philo	*top;
	t_philo	*new_philo;
	int		i;

	i = 1;
	head = NULL;
	top = NULL;
	data->time = start_time(data);
	while (i <= p->philo_num)
	{
		new_philo = create_philo(p, data, i);
		if (head == NULL)
			head = new_philo;
		else
			top->next = new_philo;
		top = new_philo;
		i++;
	}
	top->next = head;
	return (head);
}

void	param_init(char **av, int ac, t_param *table)
{
	table->philo_num = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	pthread_mutex_init(&table->print_mutex, NULL);
	if (ac == 6)
		table->must_eat_num = ft_atoi(av[5]);
}

t_philo	*create_philo(t_param *p, t_data *data, int i)
{
	t_philo	*new_philo;

	new_philo = malloc(sizeof(t_philo));
	if (!new_philo)
	{
		free(new_philo);
		return (0);
	}
	new_philo->id = i;
	new_philo->par = p;
	new_philo->data = data;
	new_philo->meals_n = 0;
	new_philo->dead = 0;
	pthread_mutex_init(&new_philo->last_meal_mutex, NULL);
	pthread_mutex_init(&new_philo->meals_mutex, NULL);
	pthread_mutex_init(&new_philo->dead_mutex, NULL);
	pthread_mutex_init(&(new_philo->fork), NULL);
	new_philo->next = NULL;
	return (new_philo);
}

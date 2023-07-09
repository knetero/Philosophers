/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 10:36:12 by abazerou          #+#    #+#             */
/*   Updated: 2023/07/09 21:08:00 by abazerou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_values(char **av, int ac)
{
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[1]) > 200 || ft_atoi(av[1]) == -1)
		return(printf("[Error]: arg not valid!\n"), -1);
	else if (ft_atoi(av[2]) < 60 || ft_atoi(av[2]) == -1)
		return(printf("[Error]: arg not valid!\n"), -1);
	else if (ft_atoi(av[3]) < 60 || ft_atoi(av[3]) == -1)
		return(printf("[Error]: arg not valid!\n"), -1);
	else if (ft_atoi(av[4]) < 60 || ft_atoi(av[4]) == -1)
		return(printf("[Error]: arg not valid!\n"), -1);
	else if (ac == 6)
	{
		if (ft_atoi(av[5]) <= 0 || ft_atoi(av[5]) == -1)
			return(printf("[Error]: arg not valid!\n"), -1);
	}
	return(0);
}

int	ft_destroy(t_philo *philo)
{
	t_philo	*current;
	t_philo	*next;
	int		num;
	int		i;

	i = 1;
	num = philo->par->philo_num;
	pthread_mutex_unlock(&philo->data->print_mutex);
	pthread_mutex_unlock(&philo->data->death_mutex);
	if(pthread_mutex_destroy(&philo->data->print_mutex) != 0)
		return(printf("[Error]: faild to destroy print_mutex!\n"), -1);
	if(pthread_mutex_destroy(&philo->data->death_mutex) != 0)
		return(printf("[Error]: faild to destroy death_mutex!\n"), -1);
	current = philo;
	while (i <= num)
	{
		next = current->next;
		pthread_mutex_unlock(&current->fork);
		if(pthread_mutex_destroy(&current->fork) != 0)
			return(printf("[Error]: faild to destroy forks!\n"), -1);
		free(current);
		current = next;
		i++;
	}
	return(0);
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_param	par;
	t_data	data;
	if (ac == 5 || ac == 6)
	{
		if(check_values(av, ac) == -1)
			return(1);
		param_init(av, ac, &par);
		philo = ft_make_philo(&par, &data);
		if(start_threads(&par, philo, ac) == -1)
			return(1);
		if(ft_destroy(philo) == -1)
			return(1);
	}
	else
		return(printf("[Error]: check your args!\n"), 1);
}

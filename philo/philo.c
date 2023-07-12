/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 10:36:12 by abazerou          #+#    #+#             */
/*   Updated: 2023/07/12 19:47:01 by abazerou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_values(char **av, int ac)
{
	if (ft_atoi(av[1]) == -1)
		return (printf("[Error]: arg not valid!\n"), -1);
	else if (ft_atoi(av[2]) == -1)
		return (printf("[Error]: arg not valid!\n"), -1);
	else if (ft_atoi(av[3]) == -1)
		return (printf("[Error]: arg not valid!\n"), -1);
	else if (ft_atoi(av[4]) == -1)
		return (printf("[Error]: arg not valid!\n"), -1);
	else if (ac == 6)
	{
		if (ft_atoi(av[5]) <= 0 || ft_atoi(av[5]) == -1)
			return (printf("[Error]: arg not valid!\n"), -1);
	}
	return (0);
}

int	ft_destroy(t_philo *philo)
{
	int		num;
	int		i;

	i = 0;
	num = philo->par->philo_num;
	pthread_mutex_destroy(&philo->par->print_mutex);
	while (i < num)
	{
		pthread_mutex_destroy(&philo->meals_mutex);
		pthread_mutex_destroy(&philo->last_meal_mutex);
		philo = philo->next;
		i++;
	}
	return (0);
}
void ff()
{
	system("leaks philo");
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_param	par;
	t_data	data;
// atexit(ff);
	if (ac == 5 || ac == 6)
	{
		if (check_values(av, ac) == -1)
			return (1);
		if (param_init(av, ac, &par) == 1)
			return(0);
		philo = ft_make_philo(&par, &data);
		start_threads(philo);
		while (1)
		{
			if (check_death(philo, ac) == 1)
				break ;
			usleep(200);
		}
		ft_destroy(philo);
	}
	else
		return (printf("[Error]: check your args!\n"), 1);
}

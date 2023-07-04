/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 10:36:12 by abazerou          #+#    #+#             */
/*   Updated: 2023/07/04 17:59:24 by abazerou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_values(char **av, int ac)
{
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[1]) > 200)
		ft_puterror("[Error]: Number of philosophers is not valid!\n");
	else if (ft_atoi(av[2]) < 60)
		ft_puterror("[Error]: time to die not valid!\n");
	else if (ft_atoi(av[3]) < 60)
		ft_puterror("[Error]: time to eat not valid!\n");
	else if (ft_atoi(av[4]) < 60)
		ft_puterror("[Error]: time to sleep not valid!\n");
	else if (ac == 6)
	{
		if (ft_atoi(av[5]) <= 0)
			ft_puterror("[Error]: eating number, must be greater than 0!\n");
	}
}

void	ft_destroy(t_philo *philo)
{
	t_philo	*current;
	t_philo	*next;
	int		i;

	i = 1;
	pthread_mutex_unlock(&philo->data->print_mutex);
	if (pthread_mutex_destroy(&philo->data->print_mutex) != 0)
		ft_puterror("error_mutex_print\n");
	current = philo;
	while (i <= philo->par->philo_num)
	{
		next = current->next;
		pthread_mutex_unlock(&current->fork);
		if (pthread_mutex_destroy(&current->fork) != 0)
			printf("error_mutex_fork %d\n", i);
		free(current);
		current = next;
		i++;
	}
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_param	par;
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		check_values(av, ac);
		param_init(av, ac, &par);
		philo = ft_make_philo(&par, &data);
		start_threads(&par, philo, ac);
		ft_destroy(philo);
	}
	else
		ft_puterror("[Error]: check your args!\n");
}

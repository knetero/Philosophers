/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 10:36:12 by abazerou          #+#    #+#             */
/*   Updated: 2023/06/26 10:38:28 by abazerou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


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
	if(!ft_isdigit(str[i]) && str[i])
		ft_puterror("[Error]:the arg is not digit!\n");
	return (result);
}

void	check_values(char **av, int ac)
{
	if(ft_atoi(av[1]) < 1)
		ft_puterror("[Error]: must be at least one philo!\n");
	else if(ft_atoi(av[2]) <= 0)
		ft_puterror("[Error]: time to die must be greater than 0!\n");
	else if(ft_atoi(av[3]) <= 0)
		ft_puterror("[Error]: time to eat must be greater than 0!\n");
	else if(ft_atoi(av[4]) <= 0)
		ft_puterror("[Error]: time to sleep must be greater than 0!\n");
    else if(ac == 6)
    {
        if(ft_atoi(av[5]) <= 0)
            ft_puterror("[Error]: must eating number, must be greater than 0!\n");
    }
}
 
void	param_init(char **av, int ac, t_param *table)
{
	table->philo_num = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
    if(ac == 6)
	    table->must_eat_num = ft_atoi(av[5]);
}
t_philo	*create_philo(void)
{
	t_philo	*new_philo;

	new_philo = malloc(sizeof(t_philo));
	if (!new_philo)
	{
		free(new_philo);
		return (0);
	}
    new_philo->par = NULL;
    new_philo->next = NULL;
	return (new_philo);
}

t_philo *ft_make_philo(t_param *p) 
{
    t_philo *head = NULL;
    t_philo *top = NULL;
    int i = 1;

    while (i <= p->philo_num) 
	{
        t_philo *new_philo = create_philo();
        new_philo->id = i;
        new_philo->par = p;
        pthread_mutex_init(&(new_philo->fork), NULL);
        new_philo->next = NULL;
        if (head == NULL) 
		{
            head = new_philo;
            top = new_philo;
        } 
        else 
		{
            top->next = new_philo;
            top = new_philo;
        }
        i++;
    }
	top->next = head;
	return(head);
}

void	ft_usleep(time_t time)
{
	time_t	current_time;

	current_time = get_time();
	while ((get_time() - current_time) < time)
		usleep(100);
}
long get_time(void) 
{
    long timestamp_ms;
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    return(timestamp_ms = (current_time.tv_sec * 1000 + current_time.tv_usec / 1000));
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
   
    int id = philo->id;
    philo->is_dead = 0;
    if(id % 2 == 0)
        usleep(200);
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);
    gettimeofday(&philo->start_time, NULL);
    long start_time = philo->start_time.tv_sec * 1000 + philo->start_time.tv_usec / 1000;
	while (1)
	{
        pthread_mutex_lock(&(philo->fork));
        printf("[%ldms] Philo %d picked up the left fork.\n", get_time() - start_time, id);
        pthread_mutex_lock(&(philo->next->fork));
        printf("[%ldms] Philo %d picked up the right fork.\n", get_time() - start_time, id);
        philo->last_meal_time = get_time();
        printf("[%ldms] Philo %d is eating.\n", get_time() - start_time, id);
        // philo->meals_n++;
        ft_usleep(philo->par->time_to_eat);
        pthread_mutex_unlock(&(philo->fork));
        pthread_mutex_unlock(&(philo->next->fork));
        printf("[%ldms] Philo %d is sleeping.\n", get_time() - start_time, id);
        ft_usleep(philo->par->time_to_sleep);
        printf("[%ldms] Philo %d is thinking.\n", get_time() - start_time, id);
        pthread_mutex_lock(&mutex);
        // if (!(philo->is_dead))
        // {
        //     long current_time = get_time();
        //     philo->time_since_last_meal = current_time - philo->last_meal_time / 1000;

        //     if (philo->time_since_last_meal > philo->par->time_to_die)
        //     {
        //         printf("[%ldms] Philo %d is dead.\n", get_time() - start_time, id);
        //         philo->is_dead = 1;
        //         pthread_mutex_unlock(&mutex);
        //         break;
        //     }
        // }
        pthread_mutex_unlock(&mutex);
	}
	return (NULL);
}

int main(int ac, char **av) 
{
    t_param par;
    t_philo *philo;
    if (ac == 5 || ac == 6)
    {
        check_values(av, ac);
        param_init(av, ac, &par);
        philo = ft_make_philo(&par);
        int i = 1;
        while (i <= par.philo_num) 
        {
            if (pthread_create(&philo->thread, NULL, &routine, philo) != 0)
                ft_puterror("[Error]: failed to create thread!\n");
            philo = philo->next;
            i++;
        }
        i = 1;
        while (i < par.philo_num) 
        {
            if (pthread_join(philo->thread, NULL) != 0)
                ft_puterror("[Error]:!\n");
            i++;
        }
    }
    else 
        ft_puterror("[Error]: check your args!\n");
}
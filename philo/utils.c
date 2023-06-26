/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 10:46:00 by abazerou          #+#    #+#             */
/*   Updated: 2023/06/19 17:50:08 by abazerou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_puterror(char *s)
{
	ft_putstr_fd(s, 1);
	exit(1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

// void	ft_lstadd_front(t_philo **lst, t_philo *new)
// {
// 	if (!lst || !new)
// 		return ;
// 	new->next = *lst;
// 	*lst = new;
// }

// t_philo	*ft_lstnew(int *content)
// {
// 	t_philo	*new;

// 	new = malloc(sizeof(t_philo));
// 	if (!new)
// 		return (NULL);
// 	new->id = content;
// 	new->next = NULL;
// 	return (new);
// }

// int	ft_lstadd_front(t_philo **alst, t_philo *new)
// {
// 	if (new)
// 	{
// 		new->next = *alst;
// 		*alst = new;
// 		new = NULL;
// 	}
// }
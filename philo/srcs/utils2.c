/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phabets <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:17:43 by phabets           #+#    #+#             */
/*   Updated: 2022/12/02 17:04:36 by phabets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		nb = -nb;
		ft_putchar_fd('-', fd);
	}
	if (nb >= 10)
	{
		ft_putnbr_fd((nb / 10), fd);
	}
	ft_putchar_fd((nb % 10 + 48), fd);
}

void	clean_all(t_philo *philo)
{
	int	i;

	i = 0;
	if (!philo)
		return ;
	while (i < philo->data->nb_philo)
	{
		pthread_mutex_destroy(&philo[i].fork_r);
		i++;
	}
	pthread_mutex_destroy(&philo->data->m_print);
	pthread_mutex_destroy(&philo->data->m_meal);
	pthread_mutex_destroy(&philo->data->m_time);
	pthread_mutex_destroy(&philo->data->m_stop);
	free(philo->data->tv);
	free(philo->data);
	free(philo);
}

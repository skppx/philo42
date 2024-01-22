/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phabets <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:13:30 by phabets           #+#    #+#             */
/*   Updated: 2022/12/02 15:59:17 by phabets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_print);
	if (!philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->m_print);
		return ;
	}
	printf("%li %i has taken a fork\n", get_time(philo->data), philo->num_philo);
	pthread_mutex_unlock(&philo->data->m_print);
}

void	print_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_print);
	if (!philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->m_print);
		return ;
	}
	printf("%li %i is eating\n", get_time(philo->data), philo->num_philo);
	pthread_mutex_unlock(&philo->data->m_print);
}

void	print_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_print);
	if (!philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->m_print);
		return ;
	}
	printf("%li %i is sleeping\n", get_time(philo->data), philo->num_philo);
	pthread_mutex_unlock(&philo->data->m_print);
}

void	print_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_print);
	if (!philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->m_print);
		return ;
	}
	printf("%li %i is thinking\n", get_time(philo->data), philo->num_philo);
	pthread_mutex_unlock(&philo->data->m_print);
	if ((philo->data->nb_philo % 2)
		&& (philo->data->t_eat >= philo->data->t_sleep))
		usleep(((philo->data->t_eat - philo->data->t_sleep) * 1000) + 1000);
}

void	print_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_print);
	printf("%li %i died\n", get_time(philo->data), philo->num_philo);
	pthread_mutex_unlock(&philo->data->m_print);
}

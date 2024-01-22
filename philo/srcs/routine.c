/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phabets <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:14:12 by phabets           #+#    #+#             */
/*   Updated: 2022/11/30 21:08:07 by phabets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fork_lock(t_philo *philo)
{
	if (philo->num_philo % 2)
	{
		pthread_mutex_lock(&philo->fork_r);
		print_fork(philo);
		pthread_mutex_lock(philo->fork_l);
		print_fork(philo);
	}
	else
	{
		pthread_mutex_lock(philo->fork_l);
		print_fork(philo);
		pthread_mutex_lock(&philo->fork_r);
		print_fork(philo);
	}
}

void	fork_unlock(t_philo *philo)
{
	if (philo->num_philo % 2)
	{
		pthread_mutex_unlock(&philo->fork_r);
		pthread_mutex_unlock(philo->fork_l);
	}
	else
	{
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(&philo->fork_r);
	}
}

void	ft_eat(t_philo *philo)
{
	fork_lock(philo);
	print_eat(philo);
	pthread_mutex_lock(&philo->data->m_meal);
	philo->last_meal = get_time(philo->data);
	pthread_mutex_unlock(&philo->data->m_meal);
	ft_usleep(philo->data, philo->data->t_eat);
	pthread_mutex_lock(&philo->data->m_meal);
	philo->meal_count += 1;
	pthread_mutex_unlock(&philo->data->m_meal);
	fork_unlock(philo);
}

int	is_dead(t_philo *philo)
{
	int	t_meal;

	pthread_mutex_lock(&philo->data->m_meal);
	t_meal = get_time(philo->data) - philo->last_meal;
	if (t_meal >= philo->data->t_die)
	{
		pthread_mutex_unlock(&philo->data->m_meal);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->m_meal);
	return (1);
}

void	*routine(void	*phil)
{
	t_philo	*philo;

	philo = (t_philo *)phil;
	if (philo->num_philo % 2 == 0)
		if (!ft_usleep(philo->data, philo->data->t_eat))
			return (0);
	while (1)
	{
		pthread_mutex_lock(&philo->data->m_stop);
		if (!philo->alive || !philo->data->stop)
		{
			pthread_mutex_unlock(&philo->data->m_stop);
			return (0);
		}
		pthread_mutex_unlock(&philo->data->m_stop);
		ft_eat(philo);
		print_sleep(philo);
		ft_usleep(philo->data, philo->data->t_sleep);
		print_think(philo);
	}
	return (0);
}

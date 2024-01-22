/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phabets <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:46:49 by phabets           #+#    #+#             */
/*   Updated: 2022/12/02 17:00:21 by phabets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_philo *philo)
{
	if (!philo->data->nb_meal)
		return ;
	pthread_mutex_lock(&philo->fork_r);
	print_fork(philo);
	ft_usleep(philo->data, philo->data->t_die);
	print_dead(philo);
	pthread_mutex_unlock(&philo->fork_r);
}

int	philo_pthread_create(t_philo *philo, int nb_philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->data->m_stop);
	pthread_mutex_lock(&philo->data->m_print);
	while (i < nb_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]))
		{
			pthread_mutex_unlock(&philo->data->m_stop);
			pthread_mutex_unlock(&philo->data->m_print);
			return (0);
		}
		i++;
	}
	pthread_mutex_unlock(&philo->data->m_stop);
	pthread_mutex_unlock(&philo->data->m_print);
	return (1);
}

void	death_checker(t_philo *philo, int nb_philo)
{
	int	i;

	i = 0;
	while (1)
	{
		if (i >= nb_philo)
			i = 0;
		if (!is_dead(&philo[i]))
		{
			pthread_mutex_lock(&philo->data->m_stop);
			pthread_mutex_lock(&philo->data->m_print);
			philo[i].alive = 0;
			philo->data->stop = 0;
			pthread_mutex_unlock(&philo->data->m_stop);
			pthread_mutex_unlock(&philo->data->m_print);
			print_dead(&philo[i]);
			pthread_join(philo[i].thread, NULL);
			break ;
		}
		if (full_checker(philo, nb_philo))
			break ;
		usleep(50);
		i++;
	}
}

void	philo_ending(t_philo *philo, int nb_philo)
{
	int	i;

	i = -1;
	while (++i < nb_philo)
	{
		pthread_mutex_lock(&philo->data->m_stop);
		pthread_mutex_lock(&philo->data->m_print);
		if (philo[i].alive != 0)
		{
			philo[i].alive = 0;
			pthread_mutex_unlock(&philo->data->m_stop);
			pthread_mutex_unlock(&philo->data->m_print);
			pthread_join(philo[i].thread, NULL);
		}
		else
		{
			pthread_mutex_unlock(&philo->data->m_stop);
			pthread_mutex_unlock(&philo->data->m_print);
		}
	}
}

void	philo_dinning(t_philo *philo)
{
	int	nb_philo;

	if (!philo)
		return ;
	nb_philo = philo->data->nb_philo;
	time_begin(philo->data);
	if (nb_philo == 1)
	{
		one_philo(philo);
		return ;
	}
	if (philo_pthread_create(philo, nb_philo))
		death_checker(philo, nb_philo);
	philo_ending(philo, nb_philo);
}

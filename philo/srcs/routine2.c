/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phabets <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:36:01 by phabets           #+#    #+#             */
/*   Updated: 2022/12/02 14:47:58 by phabets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_meal);
	if (philo->data->nb_meal <= philo->meal_count)
	{
		pthread_mutex_unlock(&philo->data->m_meal);
		philo->full = 1;
		return (0);
	}
	pthread_mutex_unlock(&philo->data->m_meal);
	return (1);
}

int	full_checker(t_philo *philo, int nb_philo)
{
	int	i;
	int	full_philo_count;

	full_philo_count = 0;
	i = 0;
	if (philo->data->nb_meal == -1)
		return (0);
	while (i < nb_philo)
	{
		if (!is_full(&philo[i]))
			full_philo_count++;
		else
			break ;
		i++;
	}
	if (full_philo_count == nb_philo)
	{
		pthread_mutex_lock(&philo->data->m_stop);
		pthread_mutex_lock(&philo->data->m_print);
		philo->data->stop = 0;
		pthread_mutex_unlock(&philo->data->m_stop);
		pthread_mutex_unlock(&philo->data->m_print);
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phabets <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:02:01 by phabets           #+#    #+#             */
/*   Updated: 2022/12/01 14:42:57 by phabets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo_data	*init_philo_data(char **av)
{
	t_philo_data	*data;

	data = malloc(sizeof(t_philo_data));
	if (!data)
		return (0);
	data->nb_philo = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	if (av[5])
		data->nb_meal = ft_atoi(av[5]);
	else
		data->nb_meal = -1;
	data->stop = 1;
	data->tv = malloc(sizeof(struct timeval));
	if (!data->tv)
	{
		free(data);
		return (NULL);
	}
	return (data);
}

void	init_philo_table_data(t_philo *philo, int i)
{
	philo->meal_count = 0;
	philo->num_philo = (i + 1);
	philo->alive = 1;
	philo->last_meal = 0;
	philo->full = 0;
}

int	init_mutex(t_philo_data *data)
{
	if (pthread_mutex_init(&data->m_print, NULL))
		return (1);
	if (pthread_mutex_init(&data->m_meal, NULL))
		return (1);
	if (pthread_mutex_init(&data->m_time, NULL))
		return (1);
	if (pthread_mutex_init(&data->m_stop, NULL))
		return (1);
	return (0);
}

t_philo	*init_philo_table(t_philo_data *data)
{
	t_philo	*philo;
	int		i;

	i = -1;
	if (init_mutex(data))
		return (NULL);
	philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!philo)
		return (0);
	while (++i < data->nb_philo)
	{
		init_philo_table_data(&philo[i], i);
		if (i != 0)
			philo[i].fork_l = &philo[i - 1].fork_r;
		if (pthread_mutex_init(&philo[i].fork_r, NULL))
			return (NULL);
		if (i == (data->nb_philo - 1))
			philo[0].fork_l = &philo[i].fork_r;
		philo[i].data = data;
	}
	return (philo);
}

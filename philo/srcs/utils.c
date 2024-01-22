/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phabets <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:40:10 by phabets           #+#    #+#             */
/*   Updated: 2022/11/24 18:41:53 by phabets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

void	time_begin(t_philo_data *data)
{
	gettimeofday(data->tv, NULL);
	data->t_start = data->tv->tv_sec * 1000 + data->tv->tv_usec / 1000;
}

long int	get_time(t_philo_data *data)
{
	long int	t;

	pthread_mutex_lock(&data->m_time);
	gettimeofday(data->tv, NULL);
	t = (data->tv->tv_sec * 1000 + data->tv->tv_usec / 1000) - data->t_start;
	pthread_mutex_unlock(&data->m_time);
	return (t);
}

int	ft_usleep(t_philo_data *data, int time)
{
	long int	t_start;
	int			ret;
	int			time_sleep;

	ret = 1;
	if (time > data->t_die)
	{
		time = data->t_die;
		ret = 0;
	}
	time_sleep = time * 100;
	t_start = get_time(data);
	while ((get_time(data) - t_start) < time)
		usleep(time_sleep);
	return (ret);
}

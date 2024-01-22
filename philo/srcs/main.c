/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phabets <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:51:58 by phabets           #+#    #+#             */
/*   Updated: 2022/12/02 14:19:51 by phabets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **args)
{
	t_philo			*philo;
	t_philo_data	*data;

	if (check_pars_philo(args, argc))
	{
		write(2, "Error\n", 6);
		return (0);
	}
	data = init_philo_data(args);
	philo = init_philo_table(data);
	if (data->nb_philo && data->nb_meal)
	{
		philo_dinning(philo);
		clean_all(philo);
	}
	else
	{
		free(philo);
		free(data->tv);
		free(data);
	}
	return (0);
}

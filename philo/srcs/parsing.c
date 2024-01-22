/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phabets <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:52:02 by phabets           #+#    #+#             */
/*   Updated: 2022/12/01 14:41:33 by phabets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	ft_atoi(const char *nptr)
{
	int			i;
	long int	res;
	int			sign;

	sign = 1;
	res = 0;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (res > INT_MAX)
			return (-1);
		res = res * 10 + nptr[i] - '0';
		i++;
	}
	return (res * sign);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	check_num(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		if (!ft_strlen(args[i]))
			return (1);
		while (args[i][j])
		{
			if (!ft_isdigit(args[i][j]))
				return (1);
			j++;
		}
		if (ft_atoi(args[i]) > INT_MAX || ft_atoi(args[i]) == -1)
			return (1);
		i++;
	}
	return (0);
}

int	check_pars_philo(char **args, int argc)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
	{
		ft_putendl_fd("Use only 4 or 5 argument", 2);
		return (1);
	}
	else
	{
		if (check_num(args))
		{
			ft_putendl_fd("Arguments must be positive int", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

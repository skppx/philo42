/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phabets <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:35:20 by phabets           #+#    #+#             */
/*   Updated: 2022/12/01 13:39:38 by phabets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <stdio.h>
# include <limits.h>

//-----Struct-------//
typedef struct s_philo_data
{
	struct timeval	*tv;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_meal;
	pthread_mutex_t	m_time;
	pthread_mutex_t	m_stop;
	int				stop;
	int				nb_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nb_meal;
	long int		t_start;
}	t_philo_data;

typedef struct s_philo
{
	t_philo_data	*data;
	int				meal_count;
	int				num_philo;
	int				alive;
	int				full;
	long int		last_meal;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	fork_r;
	pthread_t		thread;
}	t_philo;
//-----Parsing------//
long int		ft_atoi(const char *nptr);
int				check_pars_philo(char **args, int argc);
int				ft_isdigit(int c);
void			ft_putendl_fd(char *s, int fd);
void			ft_putstr_fd(char *s, int fd);
//------Init------//
t_philo_data	*init_philo_data(char **av);
t_philo			*init_philo_table(t_philo_data *data);
//------Print------//
void			print_fork(t_philo *philo);
void			print_eat(t_philo *philo);
void			print_sleep(t_philo *philo);
void			print_think(t_philo *philo);
void			print_dead(t_philo *philo);
//------Philo------//
void			philo_dinning(t_philo *philo);
void			philo_ending(t_philo *philo, int nb_philo);
//------Routine------//
int				is_dead(t_philo *philo);
void			*routine(void	*philo);
//------Routine2-----//
int				full_checker(t_philo *philo, int nb_philo);
int				is_full(t_philo *philo);
//------Utils------//
void			time_begin(t_philo_data *data);
long int		get_time(t_philo_data *data);
int				ft_usleep(t_philo_data *data, int time);
//------Utils2------//
void			ft_putchar_fd(char c, int fd);
void			ft_putnbr_fd(int n, int fd);
void			clean_all(t_philo *philo);
#endif

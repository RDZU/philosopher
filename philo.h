/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 08:07:31 by razamora          #+#    #+#             */
/*   Updated: 2024/11/10 16:01:33 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				nb_eat;
	int				l_fork_id;
	int				r_fork_id;
	struct s_table	*rule;
	pthread_mutex_t	nb_eat_mutex;
	long long		t_last_meal;
	pthread_mutex_t	*eat_lock;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_t		thread_id;
}					t_philo;

typedef struct s_table
{
	int				nb_philos;
	int				nb_eat;
	unsigned long	time_die;
	unsigned long	time_eat;
	unsigned long	time_sleep;
	int				finish;
	pthread_mutex_t	*forks;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	init_philos;
	t_philo			*philos;
}					t_table;

size_t				get_time(void);
size_t				ft_strlen(const char *s);
int					ft_is_numeric(const char *str);
long				ft_atoi(const char *str);
void				*philosopher(void *v_philo);
void				*monitoring_dead(void *v_philo);
int					ft_check_argv(int argc, char **argv, t_table **table);
void				safe_mutex(t_table *table);
int					is_dinner_ending(t_philo *philo);
void				ft_usleep(size_t milliseconds, t_philo *philo);
void				print_msm(long time, int id, char *str, t_philo *philo);
int					case_one_philo(int num_philo, t_philo *philo);
int					is_full(t_philo *philo);
void				eating_ts(t_philo *philo, t_table *table, long start_time);

#endif

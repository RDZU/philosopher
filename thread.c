/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 07:33:51 by razamora          #+#    #+#             */
/*   Updated: 2024/11/10 14:30:58 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msm(long time, int id, char *str, t_philo *philo)
{
	if (is_dinner_ending(philo) == 0)
	{
		pthread_mutex_lock(philo->write_lock);
		printf("%lu %d %s\n", get_time() - time, id, str);
		pthread_mutex_unlock(philo->write_lock);
	}
}

static int	take_forks_odd(t_philo *philo, t_table *table)
{
	usleep(9);
	pthread_mutex_lock(&(table->forks[philo->r_fork_id]));
	usleep(9);
	pthread_mutex_lock(&(table->forks[philo->l_fork_id]));
	return (0);
}

static int	take_forks_even(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(&(table->forks[philo->l_fork_id]));
	pthread_mutex_lock(&(table->forks[philo->r_fork_id]));
	return (0);
}

static void	printf_take_fork(t_philo *philo, unsigned long start_time, int id)
{
	print_msm(start_time, id, "has taken a fork", philo);
	print_msm(start_time, id, "has taken a fork", philo);
}

void	*philosopher(void *v_philo)
{
	t_philo			*philo;
	t_table			*table;
	unsigned long	start_time;

	philo = (t_philo *)v_philo;
	table = philo->rule;
	start_time = get_time();
	pthread_mutex_lock(&table->init_philos);
	pthread_mutex_unlock(&table->init_philos);
	if (case_one_philo(table->nb_philos, philo) == 1)
		return (NULL);
	if (philo->id % 2 == 1)
		ft_usleep(table->time_eat, philo);
	while (((is_full(philo)) == 0 || table->nb_eat == -1) && \
	is_dinner_ending(philo) == 0)
	{
		if (philo->id % 2)
			take_forks_odd(philo, table);
		else if (philo->id % 2 == 0)
			take_forks_even(philo, table);
		printf_take_fork(philo, start_time, philo->id);
		eating_ts(philo, table, start_time);
	}
	return (NULL);
}

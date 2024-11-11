/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:58:44 by razamora          #+#    #+#             */
/*   Updated: 2024/11/10 14:22:23 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	leave_forks_even(t_philo *philo, t_table *table)
{
	pthread_mutex_unlock(&table->forks[philo->l_fork_id]);
	pthread_mutex_unlock(&table->forks[philo->r_fork_id]);
}

static void	leave_forks_odd(t_philo *philo, t_table *table)
{
	pthread_mutex_unlock(&table->forks[philo->r_fork_id]);
	pthread_mutex_unlock(&table->forks[philo->l_fork_id]);
}

void	eating_ts(t_philo *philo, t_table *table, long start_time)
{
	print_msm(start_time, philo->id, "is eating", philo);
	pthread_mutex_lock(philo->eat_lock);
	philo->t_last_meal = get_time() - start_time;
	pthread_mutex_unlock(philo->eat_lock);
	pthread_mutex_lock(philo->eat_lock);
	philo->nb_eat++;
	pthread_mutex_unlock(philo->eat_lock);
	ft_usleep(table->time_eat, philo);
	if (philo->id % 2)
		leave_forks_odd(philo, table);
	else if (philo->id % 2 == 0)
		leave_forks_even(philo, table);
	print_msm(start_time, philo->id, "is sleeping", philo);
	ft_usleep(table->time_sleep, philo);
	print_msm(start_time, philo->id, "is thinking", philo);
}

int	is_full(t_philo *philo)
{
	t_table	*table;

	table = philo->rule;
	pthread_mutex_lock(philo->eat_lock);
	if (philo->nb_eat < table->nb_eat)
	{
		pthread_mutex_unlock(philo->eat_lock);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(philo->eat_lock);
		return (1);
	}
}

int	case_one_philo(int num_philo, t_philo *philo)
{
	unsigned long	start_time;

	start_time = get_time();
	if (num_philo == 1)
	{
		printf("%lu %d has taken a fork\n", get_time() - start_time, philo->id);
		return (1);
	}
	return (0);
}

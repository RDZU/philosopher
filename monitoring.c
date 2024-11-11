/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 07:33:44 by razamora          #+#    #+#             */
/*   Updated: 2024/11/10 14:23:51 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dinner_ending(t_philo *philo)
{
	t_table	*table;

	table = philo->rule;
	pthread_mutex_lock(philo->dead_lock);
	if (table->finish == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

static int	is_dead(t_philo *philo, t_table *table, unsigned long now, int flag)
{
	if (flag == 0)
		return (0);
	else
	{
		pthread_mutex_lock(philo->write_lock);
		printf("%lu %d died\n", now, philo->id);
		pthread_mutex_unlock(philo->write_lock);
		pthread_mutex_lock(philo->dead_lock);
		table->finish = 1;
		pthread_mutex_unlock(philo->dead_lock);
	}
	return (1);
}

static unsigned long	get_time_last_meal(t_philo *philo, unsigned long now)
{
	unsigned long	calculo;

	pthread_mutex_lock(philo->eat_lock);
	if (now > (unsigned long)philo->t_last_meal)
		calculo = now - philo->t_last_meal;
	else
		calculo = 0;
	pthread_mutex_unlock(philo->eat_lock);
	return (calculo);
}

int	is_full_monitor(t_philo *philo)
{
	t_table	*table;
	int		i;
	int		count;

	table = philo->rule;
	i = 0;
	count = 0;
	if (table->nb_eat == -1)
		return (0);
	while (i < table->nb_philos)
	{
		pthread_mutex_lock(philo->eat_lock);
		if (table->philos[i].nb_eat >= table->nb_eat)
			count++;
		pthread_mutex_unlock(philo->eat_lock);
		i++;
	}
	if (count == table->nb_philos)
	{
		return (1);
	}
	return (0);
}

void	*monitoring_dead(void *v_philo)
{
	t_philo			*philo;
	t_table			*table;
	unsigned long	now;
	unsigned long	start_time;
	int				i;

	philo = (t_philo *)v_philo;
	table = philo->rule;
	start_time = get_time();
	while (is_dinner_ending(philo) == 0)
	{
		i = 0;
		while (i < table->nb_philos)
		{
			now = get_time() - start_time;
			if (get_time_last_meal(&table->philos[i], now) > table->time_die)
				return (is_dead(philo, table, now, 1), NULL);
			else if (is_full_monitor(&table->philos[i]) == 1)
				return (NULL);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

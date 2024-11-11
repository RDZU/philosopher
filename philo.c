/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 12:23:08 by razamora          #+#    #+#             */
/*   Updated: 2024/11/10 14:59:10 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		pthread_mutex_init(&(table->forks[i]), NULL);
		i++;
	}
	pthread_mutex_init(&table->eat_lock, NULL);
	pthread_mutex_init(&table->write_lock, NULL);
	pthread_mutex_init(&table->dead_lock, NULL);
	pthread_mutex_init(&table->init_philos, NULL);
}

static void	assign_var(t_table *table, int i)
{
	table->philos[i].id = i;
	table->philos[i].nb_eat = 0;
	if (i == table->nb_philos - 1 && table->nb_philos % 2 == 1)
	{
		table->philos[i].r_fork_id = i;
		table->philos[i].l_fork_id = (i + 1) % table->nb_philos;
	}
	else
	{
		table->philos[i].l_fork_id = i;
		table->philos[i].r_fork_id = (i + 1) % table->nb_philos;
	}
	table->philos[i].rule = table;
	table->philos[i].t_last_meal = 0;
	table->philos[i].dead_lock = &table->dead_lock;
	table->philos[i].eat_lock = &table->eat_lock;
	table->philos[i].write_lock = &table->write_lock;
}

static void	cleanup_table(t_table *table, int nb_philo, int free_philo)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&table->eat_lock);
	pthread_mutex_destroy(&table->write_lock);
	pthread_mutex_destroy(&table->dead_lock);
	pthread_mutex_destroy(&table->init_philos);
	free(table->forks);
	if (free_philo == 1)
		free(table->philos);
	while (i < nb_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table);
}

int	init_philo(t_table *table, int nb_philo)
{
	int			i;
	pthread_t	time_dead;

	i = 0;
	table->philos = (t_philo *)malloc(sizeof(t_philo) * nb_philo);
	if (table->philos == NULL)
	{
		printf("Error memory philo\n");
		return (cleanup_table(table, nb_philo, 0), -1);
	}
	table->nb_philos = nb_philo;
	while (i < nb_philo)
	{
		assign_var(table, i);
		if (pthread_create(&(table->philos[i].thread_id), NULL, \
		philosopher, &(table->philos[i])) != 0)
			return (cleanup_table(table, nb_philo, 1), -1);
		i++;
	}
	if (pthread_create(&time_dead, NULL, &monitoring_dead, table->philos) != 0)
		return (cleanup_table(table, nb_philo, 1), -1);
	pthread_join(time_dead, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	*table;
	int		nb_philo;
	int		i;

	i = 0;
	table = NULL;
	if (argc >= 5 && argc <= 6)
	{
		if (ft_check_argv(argc, argv, &table))
			return (1);
		nb_philo = ft_atoi(argv[1]);
		if (nb_philo > 200)
		{
			printf("Too many philosophers\n");
			return (1);
		}
		if (init_philo(table, nb_philo) == -1)
			return (1);
		while (i < nb_philo)
			pthread_join(table->philos[i++].thread_id, NULL);
		cleanup_table(table, nb_philo, 1);
	}
	else
		printf("parameters incorrect");
	return (0);
}

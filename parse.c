/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 08:25:49 by razamora          #+#    #+#             */
/*   Updated: 2024/11/11 20:47:45 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_check_string(char *str)
{
	if (ft_is_numeric(str) == -1 || ft_strlen(str) > 11)
	{
		printf("Error arguments\n");
		return (-1);
	}
	return (0);
}

static int	ft_check_arguments(int argc, char **argv)
{
	int	i;
	int	flag;

	flag = 0;
	i = 1;
	while (i < argc)
	{
		flag = ft_check_string(argv[i]);
		if (flag == -1)
			return (-1);
		i++;
	}
	return (0);
}

static int	init_table(t_table *table, int argc, char **argv)
{
	if (ft_atoi(argv[1]) == 0 || ft_atoi(argv[2]) < 60 || \
	ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60)
	{
		printf("%s", "Incorrect parameters\n");
		return (-1);
	}
	table->nb_philos = ft_atoi(argv[1]);
	table->time_die = ft_atoi(argv[2]);
	table->time_eat = ft_atoi(argv[3]);
	table->time_sleep = ft_atoi(argv[4]);
	table->finish = 0;
	if (argc == 6)
		table->nb_eat = ft_atoi(argv[5]);
	else
		table->nb_eat = -1;
	return (0);
}

int	ft_check_argv(int argc, char **argv, t_table **table)
{
	if (ft_check_arguments(argc, argv) == -1)
		return (-1);
	*table = (t_table *)malloc(sizeof(t_table));
	if (table == NULL)
	{
		printf("Error assign memory table\n");
		return (-1);
	}
	if (init_table(*table, argc, argv) == -1)
		return (-1);
	(*table)->forks = malloc(sizeof(pthread_mutex_t) * (*table)->nb_philos);
	if ((*table)->forks == NULL)
	{
		printf("Error assign memory (*table)->philos\n");
		return (-1);
	}
	safe_mutex((*table));
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:37:55 by jlaine            #+#    #+#             */
/*   Updated: 2024/10/28 15:19:59 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static bool	create_philo(t_data *data, int i)
{
	data->pids[i] = fork();
	if (data->pids[i] == -1)
		return (false);
	if (data->pids[i] == 0)
	{
		philo_routine(&data->philos[i]);
		exit(0);
	}
	return (true);
}

int	init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->params.total_philos)
	{
		data->philos[i].id = i;
		data->philos[i].count_meal = 0;
		data->philos[i].last_meal = get_time_in_ms();
		data->philos[i].ate_enough = false;
		data->philos[i].params = &data->params;
		data->philos[i].forks = data->sem_forks;
		data->philos[i].access_fork = data->access_fork_sem;
		data->philos[i].write_sem = data->sem_write;
		data->philos[i].meal_sem = data->sem_meal;
		if (!create_philo(data, i))
			return (0);
		usleep(100);
	}
	return (1);
}

int	init_args(t_data *data, char **av)
{
	memset(data, 0, sizeof(t_data));
	data->params.start_time = get_time_in_ms();
	data->params.total_philos = ft_atoi(av[1]);
	data->params.time_to_die = ft_atoi(av[2]);
	data->params.time_to_eat = ft_atoi(av[3]);
	data->params.time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->params.max_meal = ft_atoi(av[5]);
	else
		data->params.max_meal = -1;
	data->philos = malloc(sizeof(t_philo) * data->params.total_philos);
	if (!data->philos)
		return (0);
	data->pids = malloc(sizeof(pid_t) * data->params.total_philos);
	if (!data->pids)
		return (free(data->philos), 0);
	memset(data->philos, 0, sizeof(t_philo) * data->params.total_philos);
	memset(data->pids, 0, sizeof(pid_t) * data->params.total_philos);
	return (1);
}

int	init_semaphores(t_data *data)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_ACCESS);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_MEAL);
	sem_unlink(SEM_DEATH);
	data->sem_forks = sem_open(SEM_FORKS, O_CREAT, 0644,
			data->params.total_philos);
	data->access_fork_sem = sem_open(SEM_ACCESS, O_CREAT, 0644, 1);
	data->sem_write = sem_open(SEM_WRITE, O_CREAT, 0644, 1);
	data->sem_meal = sem_open(SEM_MEAL, O_CREAT, 0644, 1);
	data->sem_reaper = sem_open(SEM_DEATH, O_CREAT, 0644, 1);
	if (data->sem_forks == SEM_FAILED || data->sem_write == SEM_FAILED
		|| data->sem_meal == SEM_FAILED || data->sem_reaper == SEM_FAILED
		|| data->access_fork_sem == SEM_FAILED)
		return (0);
	return (1);
}

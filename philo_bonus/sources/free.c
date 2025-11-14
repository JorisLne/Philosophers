/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:27:31 by jlaine            #+#    #+#             */
/*   Updated: 2024/10/28 15:19:54 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	close_and_unlink(sem_t *sem, const char *name)
{
	if (sem)
	{
		sem_close(sem);
		sem_unlink(name);
	}
}

void	sem_philo_cleaning(t_philo *philo)
{
	close_and_unlink(philo->forks, SEM_FORKS);
	close_and_unlink(philo->meal_sem, SEM_MEAL);
	close_and_unlink(philo->write_sem, SEM_WRITE);
	close_and_unlink(philo->access_fork, SEM_ACCESS);
}

void	sem_data_cleaning(t_data *data)
{
	close_and_unlink(data->sem_meal, SEM_MEAL);
	close_and_unlink(data->sem_forks, SEM_FORKS);
	close_and_unlink(data->sem_write, SEM_WRITE);
	close_and_unlink(data->sem_reaper, SEM_DEATH);
	close_and_unlink(data->access_fork_sem, SEM_ACCESS);
}

int	print_and_clean(t_data *data, char *msg)
{
	int	i;

	i = -1;
	printf("%s\n", msg);
	while (++i < data->params.total_philos)
	{
		if (data->pids && data->pids[i] > 0)
		{
			kill(data->pids[i], SIGTERM);
			waitpid(data->pids[i], NULL, 0);
		}
	}
	sem_data_cleaning(data);
	if (data->pids)
		free(data->pids);
	if (data->philos)
		free(data->philos);
	return (EXIT_FAILURE);
}

void	end_simulation(t_philo *philo, int status)
{
	sem_philo_cleaning(philo);
	exit(status);
}

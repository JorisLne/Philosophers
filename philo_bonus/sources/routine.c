/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:38:56 by jlaine            #+#    #+#             */
/*   Updated: 2024/10/28 15:20:03 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	*check_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->meal_sem);
		if (get_time_in_ms() - philo->last_meal > philo->params->time_to_die)
		{
			sem_wait(philo->write_sem);
			printf(RED"%lld %d %s\n"RESET, get_time_in_ms() \
			- philo->params->start_time, philo->id, "died");
			sem_post(philo->meal_sem);
			end_simulation(philo, 1);
		}
		sem_post(philo->meal_sem);
		usleep(1000);
	}
	return (NULL);
}

static void	alone_routine(t_philo *philo)
{
	if (philo->params->total_philos == 1)
	{
		print_status(philo, philo->id, YELL"has taken a fork"RESET);
		philo_sleep(philo->params->time_to_die);
		print_status(philo, philo->id, RED"died"RESET);
		end_simulation(philo, 1);
	}
}

static void	eat_routine(t_philo *philo)
{
	sem_wait(philo->access_fork);
	sem_wait(philo->forks);
	print_status(philo, philo->id, YELL"has taken a fork"RESET);
	sem_wait(philo->forks);
	print_status(philo, philo->id, YELL"has taken a fork"RESET);
	sem_post(philo->access_fork);
	sem_wait(philo->meal_sem);
	philo->last_meal = get_time_in_ms();
	philo->count_meal++;
	print_status(philo, philo->id, GREEN"is eating"RESET);
	sem_post(philo->meal_sem);
	philo_sleep(philo->params->time_to_eat);
	sem_post(philo->forks);
	sem_post(philo->forks);
}

static void	eat_and_sleep(t_philo *philo)
{
	while (1)
	{
		eat_routine(philo);
		if (philo->params->max_meal > 0
			&& philo->count_meal == philo->params->max_meal)
			break ;
		print_status(philo, philo->id, CYAN"is sleeping"RESET);
		philo_sleep(philo->params->time_to_sleep);
		print_status(philo, philo->id, CYAN"is thinking"RESET);
	}
}

void	philo_routine(t_philo *philo)
{
	pthread_t	death_thread;

	if (philo->id % 2 == 0)
		philo_sleep(1);
	alone_routine(philo);
	if (pthread_create(&death_thread, NULL, check_death, philo) != 0)
		end_simulation(philo, 1);
	pthread_detach(death_thread);
	eat_and_sleep(philo);
	end_simulation(philo, 2);
}

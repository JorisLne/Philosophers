/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:56:27 by jlaine            #+#    #+#             */
/*   Updated: 2024/10/15 13:11:22 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eat_and_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->params->fork_mutex[philo->fork[0]]);
	print_status(philo, YELL"has taken a fork"RESET, false);
	pthread_mutex_lock(&philo->params->fork_mutex[philo->fork[1]]);
	print_status(philo, YELL"has taken a fork"RESET, false);
	print_status(philo, GREEN"is eating"RESET, false);
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	philo_sleep(philo->params, philo->params->time_to_eat);
	if (has_simulation_stopped(philo->params) == false)
	{
		pthread_mutex_lock(&philo->last_meal_mutex);
		philo->times_ate += 1;
		pthread_mutex_unlock(&philo->last_meal_mutex);
	}
	print_status(philo, PURPLE"is sleeping"RESET, false);
	pthread_mutex_unlock(&philo->params->fork_mutex[philo->fork[0]]);
	pthread_mutex_unlock(&philo->params->fork_mutex[philo->fork[1]]);
	philo_sleep(philo->params, philo->params->time_to_sleep);
}

void	think_routine(t_philo *philo)
{
	time_t	since_last_meal;
	time_t	time_to_think;

	pthread_mutex_lock(&philo->last_meal_mutex);
	since_last_meal = get_time_in_ms() - philo->last_meal;
	time_to_think = (philo->params->time_to_die - since_last_meal \
		- philo->params->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	if (time_to_think <= 0)
		time_to_think = 1;
	else if (time_to_think > philo->params->time_to_eat)
		time_to_think = philo->params->time_to_eat;
	print_status(philo, CYAN"is thinking"RESET, false);
	philo_sleep(philo->params, time_to_think);
}

void	*alone_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->params->fork_mutex[philo->fork[0]]);
	print_status(philo, YELL"has taken a fork"RESET, false);
	philo_sleep(philo->params, philo->params->time_to_die);
	print_status(philo, RED"died"RESET, false);
	pthread_mutex_unlock(&philo->params->fork_mutex[philo->fork[0]]);
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->params->must_eat_count == 0)
		return (NULL);
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = philo->params->start_time;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	start_delay(philo->params->start_time);
	if (philo->params->time_to_die == 0)
		return (NULL);
	if (philo->params->total_philos == 1)
		return (alone_philo_routine(philo));
	else if (philo->id % 2)
		usleep(1000);
	while (has_simulation_stopped(philo->params) == false)
	{
		eat_and_sleep(philo);
		think_routine(philo);
	}
	return (NULL);
}

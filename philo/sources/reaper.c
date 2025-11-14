/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:07:17 by jlaine            #+#    #+#             */
/*   Updated: 2024/10/15 13:10:46 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	stop_flag(t_params *params, bool state)
{
	pthread_mutex_lock(&params->sim_stop_mutex);
	params->sim_stop = state;
	pthread_mutex_unlock(&params->sim_stop_mutex);
}

bool	kill_philo(t_philo *philo)
{
	time_t		current_time;
	long long	death_time;
	long long	display_time;

	current_time = get_time_in_ms();
	if ((current_time - philo->last_meal) >= philo->params->time_to_die)
	{
		stop_flag(philo->params, true);
		death_time = current_time;
		print_status(philo, RED"died"RESET, true);
		display_time = get_time_in_ms();
		if (display_time - death_time > 10)
			printf("Warning : Death message displayed after 10 ms\n");
		pthread_mutex_unlock(&philo->last_meal_mutex);
		return (true);
	}
	return (false);
}

bool	end_condition(t_params *params)
{
	unsigned int	i;
	bool			ate_enough;

	i = 0;
	ate_enough = true;
	while (i < params->total_philos)
	{
		pthread_mutex_lock(&params->philos[i]->last_meal_mutex);
		if (kill_philo(params->philos[i]))
			return (true);
		if (params->must_eat_count != -1)
			if (params->philos[i]->times_ate
				< (unsigned int)params->must_eat_count)
				ate_enough = false;
		pthread_mutex_unlock(&params->philos[i]->last_meal_mutex);
		i++;
	}
	if (params->must_eat_count != -1 && ate_enough == true)
	{
		stop_flag(params, true);
		printf(GREEN"Each philo ate %d times\n"RESET, params->must_eat_count);
		return (true);
	}
	return (false);
}

bool	has_simulation_stopped(t_params *params)
{
	bool	stop;

	pthread_mutex_lock(&params->sim_stop_mutex);
	stop = params->sim_stop;
	pthread_mutex_unlock(&params->sim_stop_mutex);
	return (stop);
}

void	*reaper_routine(void *arg)
{
	t_params	*params;

	params = (t_params *)arg;
	if (params->must_eat_count == 0)
		return (NULL);
	stop_flag(params, false);
	start_delay(params->start_time);
	while (true)
	{
		if (end_condition(params) == true)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

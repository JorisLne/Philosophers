/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:32:14 by jlaine            #+#    #+#             */
/*   Updated: 2024/10/15 13:09:00 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

pthread_mutex_t	*init_forks(t_params *params)
{
	unsigned int	i;
	pthread_mutex_t	*forks;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * params->total_philos);
	if (!forks)
		return (error_null(ERROR_MALLOC, NULL, 0));
	while (i < params->total_philos)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
			return (error_null(ERROR_MUTEX, NULL, 0));
		i++;
	}
	return (forks);
}

void	assign_forks(t_philo *philo)
{
	int	left_fork;
	int	right_fork;
	int	is_left_handed;

	left_fork = philo->id;
	right_fork = (philo->id + 1) % philo->params->total_philos;
	is_left_handed = (philo->id % 2 == 0);
	if (is_left_handed)
	{
		philo->fork[0] = left_fork;
		philo->fork[1] = right_fork;
	}
	else
	{
		philo->fork[0] = right_fork;
		philo->fork[1] = left_fork;
	}
}

bool	init_mutexes(t_params *params)
{
	params->fork_mutex = init_forks(params);
	if (!params->fork_mutex)
		return (false);
	if (pthread_mutex_init(&params->sim_stop_mutex, 0) != 0)
		return (failure(ERROR_MUTEX, NULL, params));
	if (pthread_mutex_init(&params->message_mutex, 0) != 0)
		return (failure(ERROR_MUTEX, NULL, params));
	return (true);
}

t_philo	**init_philos(t_params *params)
{
	unsigned int	i;
	t_philo			**philos;

	i = 0;
	philos = malloc(sizeof(t_philo) * params->total_philos);
	if (!philos)
		return (error_null(ERROR_MALLOC, NULL, 0));
	while (i < params->total_philos)
	{
		philos[i] = malloc(sizeof(t_philo) * 1);
		if (!philos[i])
			return (error_null(ERROR_MALLOC, NULL, 0));
		if (pthread_mutex_init(&philos[i]->last_meal_mutex, 0) != 0)
			return (error_null(ERROR_MUTEX, NULL, 0));
		philos[i]->id = i;
		philos[i]->times_ate = 0;
		philos[i]->last_meal = get_time_in_ms();
		philos[i]->params = params;
		assign_forks(philos[i]);
		i++;
	}
	return (philos);
}

t_params	*init_all(int ac, char **av)
{
	t_params	*params;

	params = malloc(sizeof(t_params) * 1);
	if (!params)
		return (error_null(ERROR_MALLOC, NULL, 0));
	params->total_philos = ft_atoi(av[1]);
	params->time_to_die = ft_atoi(av[2]);
	params->time_to_eat = ft_atoi(av[3]);
	params->time_to_sleep = ft_atoi(av[4]);
	params->must_eat_count = -1;
	if (ac - 1 == 5)
		params->must_eat_count = ft_atoi(av[5]);
	params->philos = init_philos(params);
	if (!params->philos)
		return (NULL);
	if (!init_mutexes(params))
		return (NULL);
	params->sim_stop = false;
	return (params);
}

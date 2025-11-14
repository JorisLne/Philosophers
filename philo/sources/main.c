/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:39:49 by jlaine            #+#    #+#             */
/*   Updated: 2024/10/18 16:35:16 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	start_dinner(t_params *params)
{
	unsigned int	i;
	time_t			offset;

	i = -1;
	offset = params->total_philos * 10;
	params->start_time = get_time_in_ms() + offset;
	if (params->total_philos > 1)
	{
		if (pthread_create(&params->reaper, NULL, &reaper_routine,
				params) != 0)
			return (failure(ERROR_THREAD, NULL, params));
	}
	while (++i < params->total_philos)
	{
		if (pthread_create(&params->philos[i]->thread, NULL, &philo_routine,
				params->philos[i]) != 0)
			return (failure(ERROR_THREAD, NULL, params));
	}
	return (true);
}

void	stop_dinner(t_params *params)
{
	unsigned int	i;

	i = 0;
	while (i < params->total_philos)
	{
		pthread_join(params->philos[i]->thread, NULL);
		i++;
	}
	if (params->total_philos > 1)
		pthread_join(params->reaper, NULL);
	free_mutexes(params);
	free_params(params);
}

int	main(int ac, char **av)
{
	t_params	*params;

	if (ac - 1 < 4 || ac - 1 > 5)
	{
		print_usage();
		return (EXIT_FAILURE);
	}
	if (!is_valid_input(ac, av))
		return (EXIT_FAILURE);
	params = init_all(ac, av);
	if (!params)
		return (EXIT_FAILURE);
	if (!start_dinner(params))
		return (EXIT_FAILURE);
	stop_dinner(params);
	return (EXIT_SUCCESS);
}

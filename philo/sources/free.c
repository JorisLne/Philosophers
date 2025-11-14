/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:41:32 by jlaine            #+#    #+#             */
/*   Updated: 2024/10/15 13:07:24 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*free_params(t_params *params)
{
	unsigned int	i;

	if (!params)
		return (NULL);
	if (params->fork_mutex != NULL)
		free(params->fork_mutex);
	if (params->philos != NULL)
	{
		i = 0;
		while (i < params->total_philos)
		{
			if (params->philos[i] != NULL)
				free(params->philos[i]);
			i++;
		}
		free(params->philos);
	}
	free(params);
	return (NULL);
}

void	free_mutexes(t_params *params)
{
	unsigned int	i;

	i = 0;
	while (i < params->total_philos)
	{
		pthread_mutex_destroy(&params->fork_mutex[i]);
		pthread_mutex_destroy(&params->philos[i]->last_meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&params->message_mutex);
	pthread_mutex_destroy(&params->sim_stop_mutex);
}

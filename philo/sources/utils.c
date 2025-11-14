/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:48:07 by jlaine            #+#    #+#             */
/*   Updated: 2024/10/15 13:12:16 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (result > INT_MAX || result < 1)
		return (-1);
	return ((int)result);
}

time_t	get_time_in_ms(void)
{
	struct timeval	current_time;
	time_t			milliseconds;
	time_t			seconds_to_ms;
	time_t			microsec_to_ms;

	gettimeofday(&current_time, NULL);
	seconds_to_ms = current_time.tv_sec * 1000;
	microsec_to_ms = current_time.tv_usec / 1000;
	milliseconds = seconds_to_ms + microsec_to_ms;
	return (milliseconds);
}

void	print_status(t_philo *philo, char *str, bool reaper_report)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->params->message_mutex);
	timestamp = get_time_in_ms() - philo->params->start_time;
	if (has_simulation_stopped(philo->params) == true
		&& reaper_report == false)
	{
		pthread_mutex_unlock(&philo->params->message_mutex);
		return ;
	}
	printf("%lld %d %s\n", timestamp, philo->id, str);
	pthread_mutex_unlock(&philo->params->message_mutex);
}

void	philo_sleep(t_params *params, time_t nap)
{
	time_t	wake_up;

	wake_up = get_time_in_ms() + nap;
	while (get_time_in_ms() < wake_up)
	{
		if (has_simulation_stopped(params))
			break ;
		usleep(100);
	}
}

void	start_delay(time_t start_time)
{
	while (get_time_in_ms() < start_time)
		continue ;
}

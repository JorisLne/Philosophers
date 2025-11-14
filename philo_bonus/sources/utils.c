/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:15:40 by jlaine            #+#    #+#             */
/*   Updated: 2024/10/28 14:40:05 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

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

int	print_error(char *str, char *arg)
{
	if (!arg)
		printf(str, PROG_NAME);
	else
		printf(str, PROG_NAME, arg);
	return (EXIT_FAILURE);
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

void	philo_sleep(long long time)
{
	long long	start;
	long long	cur;

	start = get_time_in_ms();
	while (1)
	{
		cur = get_time_in_ms();
		if (cur - start >= time)
			break ;
		usleep(100);
	}
}

void	print_status(t_philo *philo, int id, char *str)
{
	long long	current_time;

	sem_wait(philo->write_sem);
	current_time = get_time_in_ms() - philo->params->start_time;
	printf("%lld", current_time);
	printf(" %d", id);
	printf(" %s\n", str);
	usleep(100);
	sem_post(philo->write_sem);
}

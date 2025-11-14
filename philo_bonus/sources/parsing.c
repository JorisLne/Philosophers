/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:37:19 by jlaine            #+#    #+#             */
/*   Updated: 2024/10/23 14:09:31 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	print_usage(void)
{
	printf(RED"Usage : ./philo <number_of_philosophers> ");
	printf(RED"<time_to_die> <time_to_eat> <time_to_sleep> ");
	printf(RED"<number_of_times_each_philosopher_must_eat>\n"RESET);
}

bool	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

bool	is_valid_input(int ac, char **av)
{
	int	i;
	int	num;

	i = 1;
	while (i < ac)
	{
		if (!is_digit(av[i]))
		{
			print_error(ERROR_DIGIT, av[i]);
			return (false);
		}
		num = ft_atoi(av[i]);
		if (i == 1 && (num <= 0 || num > INT_MAX))
		{
			print_error(ERROR_PHILO, NULL);
			return (false);
		}
		if (i != 1 && num == -1)
		{
			print_error(ERROR_DIGIT, av[i]);
			return (false);
		}
		i++;
	}
	return (true);
}

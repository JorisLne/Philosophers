/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:36:36 by jlaine            #+#    #+#             */
/*   Updated: 2024/10/28 15:17:52 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	wait_philo_process(t_data *data, bool is_dead)
{
	int	i;

	i = -1;
	while (++i < data->params.total_philos)
		waitpid(data->pids[i], NULL, 0);
	if (!is_dead && data->params.max_meal > 0)
		printf(BLINK BOLD GREEN"Each philo ate %d times\n"RESET,
			data->params.max_meal);
}

static void	process_monitor(t_data *data)
{
	int		i;
	int		status;
	bool	is_dead;
	int		finished_eating;

	is_dead = false;
	finished_eating = 0;
	i = -1;
	while (finished_eating < data->params.total_philos)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 1)
		{
			is_dead = true;
			i = -1;
			while (++i < data->params.total_philos)
				if (data->pids[i] > 0)
					kill(data->pids[i], SIGKILL);
			break ;
		}
		else if (WEXITSTATUS(status) == 2)
			finished_eating++;
	}
	wait_philo_process(data, is_dead);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac - 1 < 4 || ac - 1 > 5)
	{
		print_usage();
		return (EXIT_FAILURE);
	}
	if (!is_valid_input(ac, av))
		return (EXIT_FAILURE);
	if (!init_args(&data, av))
		print_and_clean(&data, RED"Failed to init args\n"RESET);
	if (!init_semaphores(&data))
		print_and_clean(&data, RED"Failed to init semaphores\n"RESET);
	if (!init_philos(&data))
		print_and_clean(&data, RED"Failed to init philos\n"RESET);
	process_monitor(&data);
	print_and_clean(&data, BLINK BOLD GREEN"What a lunch yumyum"RESET);
	return (EXIT_SUCCESS);
}

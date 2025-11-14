/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:47:38 by jlaine            #+#    #+#             */
/*   Updated: 2024/10/14 15:23:02 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	print_error(char *str, char *arg)
{
	if (!arg)
		printf(str, PROG_NAME);
	else
		printf(str, PROG_NAME, arg);
	return (EXIT_FAILURE);
}

void	*error_null(char *str, char *arg, t_params *params)
{
	if (params != NULL)
		free_params(params);
	print_error(str, arg);
	return (NULL);
}

int	failure(char *str, char *arg, t_params *params)
{
	if (params != NULL)
		free_params(params);
	return (print_error(str, arg));
}

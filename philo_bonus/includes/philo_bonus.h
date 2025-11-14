/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:32:38 by jlaine            #+#    #+#             */
/*   Updated: 2024/10/28 15:19:48 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <semaphore.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdbool.h>
# include <limits.h>

# define PROG_NAME		"philo:"
# define ERROR_DIGIT	"%s invalid input {%s} : \
not a valid integer.\n"
# define ERROR_PHILO	"%s invalid input: \
number of philosophers must be between 1 and INT_MAX\n"
# define ERROR_SEM		"Failed to create semaphores\n"
# define ERROR_INIT		"Failed to init params\n"
# define ERROR_PHILOS	"Failed to init philos\n"

# define SEM_FORKS "/sem_forks"
# define SEM_ACCESS "/sem_access"
# define SEM_WRITE	"/sem_write"
# define SEM_MEAL	"/sem_meal"
# define SEM_DEATH	"/sem_death"

# define PHILO_DEAD 1
# define PHILO_DONE_EATING 2

# define RESET	"\e[0m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define YELL	"\e[33m"
# define PURPLE	"\e[35m"
# define CYAN	"\e[36m"
# define BLINK	"\e[5m"
# define BOLD	"\e[1m"

typedef struct s_params
{
	int			max_meal;
	int			time_to_eat;
	int			time_to_die;
	int			time_to_sleep;
	int			total_philos;
	long long	start_time;
}	t_params;

typedef struct s_philo
{
	int			id;
	long long	last_meal;
	bool		ate_enough;
	int			count_meal;
	sem_t		*forks;
	t_params	*params;
	sem_t		*meal_sem;
	sem_t		*write_sem;
	sem_t		*access_fork;
}	t_philo;

typedef struct s_data
{
	pid_t		*pids;
	t_params	params;
	t_philo		*philos;
	sem_t		*sem_forks;
	sem_t		*sem_write;
	sem_t		*sem_meal;
	sem_t		*sem_reaper;
	sem_t		*access_fork_sem;
}	t_data;

// parsing
void	print_usage(void);
bool	is_valid_input(int ac, char **av);

// init
int		init_philos(t_data *data);
int		init_semaphores(t_data *data);
int		init_args(t_data *data, char **av);

// routine
void	*check_death(void *arg);
void	philo_routine(t_philo *philo);

// utils
int		ft_atoi(char *str);
time_t	get_time_in_ms(void);
void	philo_sleep(long long time);
int		print_error(char *str, char *arg);
void	print_status(t_philo *philo, int id, char *str);

// free
void	sem_data_cleaning(t_data *data);
void	sem_philo_cleaning(t_philo *philo);
int		print_and_clean(t_data *data, char *msg);
void	end_simulation(t_philo *philo, int status);
void	close_and_unlink(sem_t *sem, const char *name);

#endif
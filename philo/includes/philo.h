/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:53:04 by jlaine            #+#    #+#             */
/*   Updated: 2024/10/15 13:06:52 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> // printf et write
# include <stdlib.h> // malloc et free
# include <string.h> // memset
# include <unistd.h> // usleep
# include <pthread.h> // gestion thread (pthread_create..)
# include <sys/time.h> // gettimeofday
# include <limits.h> // INT_MIN et INT_MAX
# include <stdbool.h> // bools

// Macros
# define RESET	"\e[0m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define YELL	"\e[33m"
# define PURPLE	"\e[35m"
# define CYAN	"\e[36m"
# define PROG_NAME		"philo:"
# define ERROR_DIGIT	"%s invalid input {%s} : \
not a valid integer.\n"
# define ERROR_PHILO	"%s invalid input: \
number of philosophers must be between 1 and INT_MAX\n"
# define ERROR_MALLOC	"%s : Couldn't allocate memory\n"
# define ERROR_MUTEX	"%s : Couldn't create mutex\n"
# define ERROR_THREAD	"%s : Couldn't create thread\n"
# define ERROR_OVERFLOW "%s : Arguments exceed INT_MIN or INT_MAX\n"

typedef struct s_philo	t_philo;

typedef struct s_params
{
	unsigned int	total_philos;
	int				must_eat_count;
	bool			sim_stop;
	time_t			start_time;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			time_to_die;
	pthread_mutex_t	sim_stop_mutex;
	pthread_mutex_t	message_mutex;
	pthread_mutex_t	*fork_mutex;
	pthread_t		reaper;
	t_philo			**philos;
}	t_params;

typedef struct s_philo
{
	pthread_t		thread;
	unsigned int	id;
	unsigned int	times_ate;
	unsigned int	fork[2];
	time_t			last_meal;
	t_params		*params;
	pthread_mutex_t	last_meal_mutex;
}	t_philo;

// errors
int				print_error(char *str, char *arg);
int				failure(char *str, char *arg, t_params *params);
void			*error_null(char *str, char *arg, t_params *params);

// free
void			*free_params(t_params *params);
void			free_mutexes(t_params *params);

// parsing
void			print_usage(void);
bool			is_digit(char *str);
bool			is_valid_input(int ac, char **av);

// utils
int				ft_atoi(char *str);
time_t			get_time_in_ms(void);
void			start_delay(time_t start_time);
void			philo_sleep(t_params *params, time_t nap);
void			print_status(t_philo *philo, char *str, bool reaper_report);

// init
t_params		*init_all(int ac, char **av);
void			assign_forks(t_philo *philo);
pthread_mutex_t	*init_forks(t_params *params);
bool			init_mutexes(t_params *params);
t_philo			**init_philos(t_params *params);

// routine
void			*philo_routine(void *arg);
void			think_routine(t_philo *philo);
void			eat_and_sleep(t_philo *philo);
void			*alone_philo_routine(t_philo *philo);

// reaper
bool			kill_philo(t_philo *philo);
void			*reaper_routine(void *arg);
bool			end_condition(t_params *params);
bool			has_simulation_stopped(t_params *params);
void			stop_flag(t_params *params, bool status);

#endif
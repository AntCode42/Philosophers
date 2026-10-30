/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agard <agard@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 10:53:20 by agard             #+#    #+#             */
/*   Updated: 2026/03/10 17:04:22 by agard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int				to_die;
	int				to_eat;
	int				to_sleep;
	int				incr;
	int				nb_philo;
	int				status;
	long			start_ms;
	pthread_mutex_t	mutex;
	pthread_mutex_t	mutex_death;
}	t_data;

typedef struct s_philo
{
	int				num;
	long			last_meal;
	int				meal_count;
	pthread_mutex_t	mutex_fork;
	pthread_t		th;
	t_data			*data;
	struct s_philo	*next;
	struct s_philo	*prev;
}	t_philo;

// action.c
void	to_eat(t_philo *philo, t_philo *runner);
void	to_sleep(t_philo *philo);
void	to_think(t_philo *philo);
int		print_action(t_philo *philo, int msg);
void	one_to_eat(t_philo *philo);

// main.c
int		main(int argc, char **argv);
void	data_init(char **argv, t_data *data);

// routine.c
void	*routine(void *arg);
int		get_status(t_data *data);

// thread_management.c
int		thread_init(t_philo **philo, t_data *data);
int		routine_init(t_philo **tmp, t_data **data);
void	mutex_fork_init(t_philo **tmp, t_data **data);

// ./utils
// end_program.c
void	free_list_circular(t_philo **philo, int n);
int		end_program(t_philo **philo, t_data *data);

// list_management.c
void	fill_list(t_philo **philo, t_data *data, int nbr);
t_philo	*new_node(int count);
void	first_node(t_philo **philo, t_philo **first,
			t_philo *node, t_philo **tmp);
void	add_back(t_philo **philo, t_philo **tmp, t_philo **node);

// monitor.c
int		monitor(t_philo *first, t_data *data);
void	dead(t_philo *philo);
int		status(t_philo *philo);
long	diff_calc(t_philo *tmp, t_data *data);
void	update_status(t_data **data);

// tools_function.c
int		ft_isalnum(char c);
int		ft_atoi(const char *nbr);
long	now_ms(void);
void	precise_sleep(long time_ms);

#endif
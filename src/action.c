/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agard <agard@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:54:34 by agard             #+#    #+#             */
/*   Updated: 2026/03/10 10:46:59 by agard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	to_eat(t_philo *philo, t_philo *runner)
{
	if (philo->num % 2 == 1)
	{
		usleep(1000);
		pthread_mutex_lock(&philo->mutex_fork);
		print_action(philo, 1);
		pthread_mutex_lock(&runner->mutex_fork);
		print_action(philo, 1);
	}
	else
	{
		pthread_mutex_lock(&runner->mutex_fork);
		print_action(philo, 1);
		pthread_mutex_lock(&philo->mutex_fork);
		print_action(philo, 1);
	}
	print_action(philo, 2);
	pthread_mutex_lock(&philo->data->mutex_death);
	philo->last_meal = now_ms();
	pthread_mutex_unlock(&philo->data->mutex_death);
	precise_sleep(philo->data->to_eat);
	pthread_mutex_lock(&philo->data->mutex_death);
	philo->meal_count++;
	pthread_mutex_unlock(&philo->data->mutex_death);
	pthread_mutex_unlock(&philo->mutex_fork);
	pthread_mutex_unlock(&runner->mutex_fork);
}

void	to_sleep(t_philo *philo)
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	pthread_mutex_lock(&philo->data->mutex);
	if (get_status(philo->data) == 0)
	{
		print_action(philo, 3);
	}
	pthread_mutex_unlock(&philo->data->mutex);
	precise_sleep(philo->data->to_sleep);
}

void	to_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex);
	if (get_status(philo->data) == 0)
		print_action(philo, 4);
	pthread_mutex_unlock(&philo->data->mutex);
}

int print_action(t_philo *philo, int msg)
{
	if (philo->data->status == 1)
		return (1);
	if (msg == 1)
		printf("%li %i has taken a fork\n",
			now_ms() - philo->data->start_ms, philo->num);
	else if (msg == 2)
		printf("%li %i is eating\n",
			now_ms() - philo->data->start_ms, philo->num);
	else if (msg == 3)
		printf("%li %i is sleeping\n",
			now_ms() - philo->data->start_ms, philo->num);
	else if (msg == 4)
		printf("%li %i is thinking\n",
			now_ms() - philo->data->start_ms, philo->num);
	return (0);
}

void	one_to_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_fork);
	print_action(philo, 1);
	pthread_mutex_unlock(&philo->mutex_fork);
}

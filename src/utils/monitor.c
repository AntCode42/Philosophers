/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agard <agard@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 14:46:44 by agard             #+#    #+#             */
/*   Updated: 2026/03/10 17:16:26 by agard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

int	monitor(t_philo *first, t_data *data)
{
	t_philo	*tmp;
	int		i;

	while (get_status(data) == 0)
	{
		tmp = first;
		i = 0;
		while (i++ < data->nb_philo)
		{
			if ((diff_calc(tmp, data)) > data->to_die)
			{
				dead(tmp);
				return (0);
			}
			if (status(tmp) == 1)
			{
				update_status(&data);
				return (0);
			}
			tmp = tmp->next;
		}
		usleep(1000);
	}
	return (0);
}

void	dead(t_philo *philo)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	pthread_mutex_lock(&philo->data->mutex_death);
	if (philo->data->status == 0)
		philo->data->status = 1;
	pthread_mutex_unlock(&philo->data->mutex_death);
	pthread_mutex_lock(&philo->data->mutex);
	printf("%li %i died\n", now_ms() - philo->data->start_ms, philo->num);
	pthread_mutex_unlock(&philo->data->mutex);
}

int	status(t_philo *philo)
{
	int		i;
	int		status;
	t_philo	*tmp;

	tmp = philo;
	i = 0;
	status = 0;
	if (tmp->data->incr <= 0)
		return (0);
	while (i < tmp->data->nb_philo)
	{
		if (tmp->meal_count >= tmp->data->incr)
			status++;
		i++;
		tmp = tmp->next;
	}
	return (status == philo->data->nb_philo);
}

long	diff_calc(t_philo *tmp, t_data *data)
{
	long	diff;

	diff = 0;
	pthread_mutex_lock(&data->mutex_death);
	diff = now_ms() - tmp->last_meal;
	pthread_mutex_unlock(&data->mutex_death);
	return (diff);
}

void	update_status(t_data **data)
{
	pthread_mutex_lock(&(*data)->mutex_death);
	(*data)->status = 1;
	pthread_mutex_unlock(&(*data)->mutex_death);
}

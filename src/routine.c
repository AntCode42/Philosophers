/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agard <agard@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 11:21:59 by agard             #+#    #+#             */
/*   Updated: 2026/03/10 11:04:40 by agard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*routine(void *arg)
{
	t_philo		*philo;
	t_philo		*tmp;
	t_philo		*runner;

	philo = (t_philo *)arg;
	tmp = philo;
	if (tmp->data->nb_philo == 1)
	{
		one_to_eat(tmp);
		return (0);
	}
	while (get_status(tmp->data) == 0)
	{
		if (get_status(philo->data) != 0)
			return (0);
		runner = tmp->next;
		to_eat(tmp, runner);
		if (get_status(philo->data) != 0)
			return (0);
		to_sleep(tmp);
		if (get_status(philo->data) != 0)
			return (0);
		to_think(tmp);
	}
	return (0);
}

int	get_status(t_data *data)
{
	int status;

	pthread_mutex_lock(&data->mutex_death);
	status = data->status;
	pthread_mutex_unlock(&data->mutex_death);
	return (status);
}

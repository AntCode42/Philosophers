/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agard <agard@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 11:17:48 by agard             #+#    #+#             */
/*   Updated: 2026/03/10 11:10:01 by agard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	thread_init(t_philo **philo, t_data *data)
{
	t_philo			*tmp;
	int				i;

	tmp = *philo;
	pthread_mutex_init(&data->mutex, NULL);
	pthread_mutex_init(&data->mutex_death, NULL);
	mutex_fork_init(&tmp, &data);
	tmp = *philo;
	data->start_ms = now_ms();
	i = 0;
	while (i++ < data->nb_philo)
		routine_init(&tmp, &data);
	tmp = *philo;
	monitor(*philo, data);
	i = 0;
	while (i++ < data->nb_philo)
	{
		if (pthread_join(tmp->th, NULL) != 0)
			return (4);
		tmp = tmp->next;
	}
	return (end_program(philo, data));
}

int	routine_init(t_philo **tmp, t_data **data)
{
	(*tmp)->last_meal = (*data)->start_ms;
	if (pthread_create(&(*tmp)->th, NULL, &routine, *tmp) != 0)
		return (3);
	*tmp = (*tmp)->next;
	return (0);
}

void	mutex_fork_init(t_philo **tmp, t_data **data)
{
	int	i;

	i = 0;
	while (i < (*data)->nb_philo)
	{
		pthread_mutex_init(&(*tmp)->mutex_fork, NULL);
		*tmp = (*tmp)->next;
		i++;
	}
}

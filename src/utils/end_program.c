/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agard <agard@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 11:06:33 by agard             #+#    #+#             */
/*   Updated: 2026/03/10 10:50:51 by agard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

void	free_list_circular(t_philo **philo, int n)
{
	t_philo	*node;
	t_philo	*next;
	int		i;

	node = *philo;
	i = 0;
	while (node && i < n)
	{
		next = node->next;
		free(node);
		node = next;
		i++;
	}
	*philo = NULL;
}

int	end_program(t_philo **philo, t_data *data)
{
	t_philo	*tmp;
	int		i;

	tmp = *philo;
	i = 0;
	while (tmp && i < data->nb_philo)
	{
		pthread_mutex_destroy(&tmp->mutex_fork);
		tmp = tmp->next;
		i++;
	}
	pthread_mutex_destroy(&data->mutex);
	pthread_mutex_destroy(&data->mutex_death);
	free_list_circular(philo, data->nb_philo);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agard <agard@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 19:51:07 by agard             #+#    #+#             */
/*   Updated: 2026/03/10 11:05:14 by agard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

void	fill_list(t_philo **philo, t_data *data, int nbr)
{
	t_philo	*node;
	t_philo	*tmp;
	t_philo	*first;
	int		i;

	i = 1;
	data->nb_philo = nbr;
	data->status = 0;
	first = NULL;
	tmp = NULL;
	while (i <= nbr)
	{
		node = new_node(i);
		node->data = data;
		if (*philo == NULL)
			first_node(philo, &first, node, &tmp);
		else
			add_back(philo, &tmp, &node);
		i++;
	}
	if (nbr > 1)
	{
		tmp->next = first;
		first->prev = tmp;
	}
}

t_philo	*new_node(int count)
{
	t_philo		*node;

	node = malloc(sizeof(t_philo));
	if (!node)
		return (NULL);
	node->num = count;
	node->last_meal = 0;
	node->meal_count = 0;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	first_node(t_philo **philo, t_philo **first,
			t_philo *node, t_philo **tmp)
{
	*philo = node;
	*first = node;
	*tmp = node;
}

void	add_back(t_philo **philo, t_philo **tmp, t_philo **node)
{
	*tmp = *philo;
	while ((*tmp)->next)
		*tmp = (*tmp)->next;
	(*tmp)->next = *node;
	(*node)->prev = *tmp;
	*tmp = *node;
}

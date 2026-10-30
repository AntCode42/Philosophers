/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agard <agard@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 10:24:11 by agard             #+#    #+#             */
/*   Updated: 2026/03/10 10:44:24 by agard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;
	int		i;
	int		j;

	philo = NULL;
	if (argc > 6 || argc < 5)
		return (1);
	i = 1;
	while (argv[i] != NULL)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (ft_isalnum(argv[i][j]) != 0)
				return (2); // error : no numerique inpute
			j++;
		}
		i++;
	}
	data_init(argv, &data);
	fill_list(&philo, &data, ft_atoi(argv[1]));
	thread_init(&philo, &data);
	return (0);
}

void	data_init(char **argv, t_data *data)
{
	data->to_die = ft_atoi(argv[2]);
	data->to_eat = ft_atoi(argv[3]);
	data->to_sleep = ft_atoi(argv[4]);
	data->incr = 0;
	if (argv[5])
		data->incr = ft_atoi(argv[5]);
}

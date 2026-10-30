/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agard <agard@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 11:57:59 by agard             #+#    #+#             */
/*   Updated: 2026/03/10 10:54:46 by agard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

int	ft_isalnum(char c)
{
	if (c >= 48 && c <= 57)
		return (0);
	return (1);
}

int	ft_atoi(const char *nbr)
{
	size_t		i;
	long int	result;
	int			neg;

	i = 0;
	neg = 0;
	result = 0;
	while ((nbr[i] >= 9 && nbr[i] <= 13) || nbr[i] == 32)
		i++;
	if (nbr[i] == '-' || nbr[i] == '+')
	{
		if (nbr[i] == '-')
			neg++;
		i++;
	}
	while (nbr[i] >= '0' && nbr[i] <= '9')
	{
		result = result * 10;
		result += nbr[i] - '0';
		i++;
	}
	if (neg != 0)
		return (result * -1);
	return (result);
}

long	now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

void	precise_sleep(long time)
{
	long start;

	start = now_ms();
	while (now_ms() - start < time)
		usleep(500);
}

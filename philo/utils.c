/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 09:16:47 by abourdar          #+#    #+#             */
/*   Updated: 2022/03/29 09:16:51 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

long int	actual_time(void)
{
	long int			time;
	struct timeval		current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		return (-1);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	ft_usleep(t_data *philo, long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = actual_time();
	while (check_alive(philo) && (actual_time() - start_time) < time_in_ms)
	{
		usleep(time_in_ms / 10);
	}
}

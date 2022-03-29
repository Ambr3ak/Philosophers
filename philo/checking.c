/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 09:00:49 by abourdar          #+#    #+#             */
/*   Updated: 2022/03/29 09:00:51 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

int	check_alive(t_data *tp)
{
	pthread_mutex_lock(&tp->c->general);
	if (tp->c->death)
	{
		pthread_mutex_unlock(&tp->c->general);
		return (0);
	}
	pthread_mutex_unlock(&tp->c->general);
	return (1);
}

void	*is_dead(void *tmp)
{
	t_data	*tp;

	tp = (t_data *)tmp;
	ft_usleep(tp, tp->ttd);
	pthread_mutex_lock(&tp->c->general);
	if ((actual_time() - tp->start_eat) >= tp->ttd)
	{
		pthread_mutex_unlock(&tp->c->general);
		print_message(tp, tp->id, "died\n");
		pthread_mutex_lock(&tp->c->general);
		tp->c->death = 1;
		pthread_mutex_unlock(&tp->c->general);
		return (NULL);
	}
	pthread_mutex_unlock(&tp->c->general);
	return (NULL);
}

int	check_times_eat(t_data *tp)
{
	int	eat;

	eat = 0;
	if (tp->c->m_eat != -1)
	{
		pthread_mutex_lock(&tp->c->general);
		eat = tp->h_eat;
		pthread_mutex_unlock(&tp->c->general);
		if (eat == tp->c->m_eat)
		{
			printf("%d count\n", tp->c->count);
			pthread_mutex_lock(&tp->c->general);
			tp->c->count++;
			pthread_mutex_unlock(&tp->c->general);
			return (1);
		}
	}
	return (0);
}

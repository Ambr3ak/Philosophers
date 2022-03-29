/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 09:15:19 by abourdar          #+#    #+#             */
/*   Updated: 2022/03/29 09:15:20 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

void	think_sleep(t_data *tp)
{
	print_message(tp, tp->id, "is sleeping\n");
	ft_usleep(tp, tp->tts);
	print_message(tp, tp->id, "is thinking\n");
}

void	eat_last_first(t_data *tp)
{
	if (tp->id % 2 == 0)
	{
		pthread_mutex_lock(tp->r_fork);
		print_message(tp, tp->id, "has taken a fork\n");
		pthread_mutex_lock(&tp->l_fork);
		print_message(tp, tp->id, "has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(&tp->l_fork);
		print_message(tp, tp->id, "has taken a fork\n");
		pthread_mutex_lock(tp->r_fork);
		print_message(tp, tp->id, "has taken a fork\n");
	}
}

void	is_eating(t_data *tp)
{
	eat_last_first(tp);
	print_message(tp, tp->id, "is eating\n");
	pthread_mutex_lock(&tp->c->general);
	tp->start_eat = actual_time();
	pthread_mutex_unlock(&tp->c->general);
	ft_usleep(tp, tp->tte);
	pthread_mutex_lock(&tp->c->general);
	tp->h_eat++;
	pthread_mutex_unlock(&tp->c->general);
	pthread_mutex_unlock(tp->r_fork);
	pthread_mutex_unlock(&tp->l_fork);
}

void	a_table(t_data *tp)
{
	if (tp->id % 2 == 0)
		ft_usleep(tp, tp->tte / 10);
	while (check_alive(tp) && !check_times_eat(tp))
	{
		is_eating(tp);
		think_sleep(tp);
	}
}

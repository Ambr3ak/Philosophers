/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 09:13:53 by abourdar          #+#    #+#             */
/*   Updated: 2022/03/29 09:13:54 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

void	*starting(void *tmp)
{
	t_data	*tp;

	tp = (t_data *)tmp;
	pthread_mutex_lock(&tp->c->general);
	tp->start_eat = actual_time();
	pthread_mutex_unlock(&tp->c->general);
	pthread_create(&tp->death, NULL, &is_dead, tp);
	if (tp->c->nbr == 1)
	{
		pthread_mutex_lock(&tp->l_fork);
		print_message(tp, tp->id, "has taken a fork\n");
		pthread_mutex_unlock(&tp->l_fork);
		while (check_alive(tp))
			ft_usleep(tp, tp->ttd);
	}
	else
		a_table(tp);
	pthread_detach(tp->death);
	return (NULL);
}

int	start_th(t_arg *arg)
{
	int	i;

	i = 0;
	arg->philo = malloc(sizeof(t_data) * arg->n_philo);
	arg->com.nbr = arg->n_philo;
	if (arg->philo)
	{
		init_philo(arg, arg->philo);
		while (i < arg->n_philo)
		{
			if (pthread_create(&arg->philo[i].th, NULL,
					&starting, (void *)&arg->philo[i]) != 0)
				exit_prog(-3, arg);
			i++;
		}
		destroy_mutex(arg, arg->philo);
		return (0);
	}
	return (-1);
}

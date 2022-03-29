/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 09:11:23 by abourdar          #+#    #+#             */
/*   Updated: 2022/03/29 09:11:24 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

void	print_message(t_data *tp, int id, char *s)
{
	pthread_mutex_lock(&tp->c->general);
	if (tp->c->death != 0)
	{
		pthread_mutex_unlock(&tp->c->general);
		return ;
	}
	pthread_mutex_unlock(&tp->c->general);
	if (check_times_eat(tp))
		return ;
	pthread_mutex_lock(&tp->c->general);
	if (!tp->c->death)
		printf("[%ld] %d %s", actual_time() - tp->c->start_th, id, s);
	pthread_mutex_unlock(&tp->c->general);
}

void	init_mutex_struct(t_arg *arg)
{
	arg->com.start_th = arg->philo[0].start_eat;
	arg->com.death = 0;
	arg->com.m_eat = arg->m_eat;
	arg->com.nbr = arg->n_philo;
	arg->com.count = 0;
	pthread_mutex_init(&arg->com.general, NULL);
}

void	init_philo(t_arg *arg, t_data *philo)
{
	int	i;

	i = 0;
	philo[0].start_eat = actual_time();
	init_mutex_struct(arg);
	while (i < arg->n_philo)
	{
		if (i != 0)
			philo[i].start_eat = philo[0].start_eat;
		philo[i].c = &arg->com;
		philo[i].id = i + 1;
		philo[i].tte = arg->ms_e;
		philo[i].tts = arg->ms_s;
		philo[i].ttd = arg->ms_d;
		if (arg->m_eat != -1)
			philo[i].h_eat = 0;
		philo[i].r_fork = NULL;
		pthread_mutex_init(&philo[i].l_fork, NULL);
		if (i == arg->n_philo - 1)
			philo[i].r_fork = &philo[0].l_fork;
		else
			philo[i].r_fork = &philo[i + 1].l_fork;
		i++;
	}
}

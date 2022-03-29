/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 09:02:32 by abourdar          #+#    #+#             */
/*   Updated: 2022/03/29 09:02:33 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

void	destroy_mutex(t_arg *arg, t_data *philo)
{
	int	i;

	i = 0;
	while (check_alive(arg->philo) && !check_times_eat(arg->philo))
		ft_usleep(arg->philo, 1);
	while (i < arg->n_philo)
	{
		if (pthread_join(arg->philo[i].th, NULL) != 0)
			exit_prog(-4, arg);
		i++;
	}
	i = 0;
	while (i < philo[0].c->nbr)
	{
		pthread_mutex_destroy(&philo[i].l_fork);
		i++;
	}
	if (philo[0].c->count)
	{
		printf("Each philo ate %d time(s)\n", philo[0].c->m_eat);
	}
	free(philo);
}

void	exit_prog(int error, t_arg *arg)
{
	if (error == 1)
		ft_putstr_fd("Error\nPlease launch ./arg arg1 arg2 arg3 arg4.\n", 2);
	if (error == -1)
		ft_putstr_fd("Error\nMalloc failed.\n", 2);
	if (error == -2)
		ft_putstr_fd("Error\nAdd a correct value.\n", 2);
	if (error == -3)
		ft_putstr_fd("Error\nFailed to create thread\n", 2);
	if (error == -4)
		ft_putstr_fd("Error\nFailed to join thread\n", 2);
	free(arg);
	exit (0);
}

int	main(int ac, char **av)
{
	t_arg	*arg;

	arg = malloc(sizeof(t_arg));
	ft_memset(arg, 0, sizeof(t_arg));
	if ((ac < 5 || ac > 6) || !arg)
		exit_prog(1, arg);
	exit_prog(parse_arg(av, ac, arg), arg);
}

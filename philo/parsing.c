/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 09:03:48 by abourdar          #+#    #+#             */
/*   Updated: 2022/03/29 09:03:49 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

void	init_var(t_arg *arg, int *arr)
{
	arg->n_philo = arr[0];
	arg->ms_d = arr[1];
	arg->ms_e = arr[2];
	arg->ms_s = arr[3];
	if (arg->ac == 5)
		arg->m_eat = arr[4];
	else
		arg->m_eat = -1;
}

int	str_is_digit(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (ERR_ARG);
		i++;
	}
	return (0);
}

int	parse_arg(char **av, int ac, t_arg *arg)
{
	int	i;

	i = 0;
	arg->args = malloc(sizeof(int) * (ac - 1));
	if (!arg->args)
		return (ERR_MALLOC);
	while (i < ac - 1)
	{
		if (str_is_digit(av[i + 1]))
			return (ERR_ARG);
		arg->args[i] = ft_atoi(av[i + 1]);
		if (arg->args[i] < 1 || ft_strlen(av[i + 1]) > 10)
			return (ERR_ARG);
		i++;
	}
	arg->ac = ac - 1;
	init_var(arg, arg->args);
	free(arg->args);
	return (start_th(arg));
}

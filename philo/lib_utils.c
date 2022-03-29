/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 09:34:48 by abourdar          #+#    #+#             */
/*   Updated: 2022/03/29 09:34:49 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

int	ft_atoi(const char *str)
{
	int			m;
	long		res;
	char		*strr;

	m = 0;
	res = 0;
	strr = (char *)str;
	while (*strr == ' ' || (*strr > 8 && *strr < 14))
		strr++;
	if (*strr == '-' || *strr == '+')
	{
		if (*strr == '-')
			m++;
		strr++;
	}
	while (*strr >= '0' && *strr <= '9')
	{
		res = res * 10 + *strr - '0';
		strr++;
	}
	if (m % 2 != 0)
		res = -res;
	return (res);
}

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	else
		return (0);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)b;
	while (i < len)
	{
		str[i] = (char)c;
		i++;
	}
	return (b);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (s[i])
		while (s[i])
			i++;
	return (i);
}

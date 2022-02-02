/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucile <jlucile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:58:11 by jlucile           #+#    #+#             */
/*   Updated: 2021/11/17 16:58:12 by jlucile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_perror(int err)
{
	if (err == 1)
		printf("Malloc error\n");
	else if (err == 2)
		printf("Mutex error\n");
	else if (err == 3)
		printf("Error during creating thread\n");
	return (1);
}

static long	to_int(const char *str, size_t i, int sign)
{
	int	rank;
	int	res;

	res = 0;
	rank = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (rank > 11 && sign == 1)
			return (-1);
		else if (rank > 11 && sign == -1)
			return (0);
		res = res * 10 + str[i] - '0';
		rank++;
		i++;
	}
	res *= sign;
	return (res);
}

int	ft_atoi(const char *str)
{
	long	res;
	size_t	i;
	int		sign;

	i = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		   || str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	res = to_int(str, i, sign);
	return ((int)res);
}

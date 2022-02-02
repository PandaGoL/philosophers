/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timenprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucile <jlucile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:58:07 by jlucile           #+#    #+#             */
/*   Updated: 2021/11/17 16:58:08 by jlucile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long	get_time(void)
{
	struct timeval	tv1;

	gettimeofday(&tv1, NULL);
	return (tv1.tv_sec * 1000 + tv1.tv_usec / 1000);
}

void	print_activ(int id, t_param *param, char *str)
{
	pthread_mutex_lock(&param->printing);
	if (param->is_dead)
		printf("%ld %d %s\n", get_time() - param->start_time, id + 1, str);
	pthread_mutex_unlock(&param->printing);
}

void	print_death(int id, t_param *param, char *str)
{
	pthread_mutex_lock(&param->printing);
	if (param->is_dead)
		printf("%ld %d %s\n", get_time() - param->start_time, id + 1, str);
	param->is_dead = 0;
	pthread_mutex_unlock(&param->printing);
}

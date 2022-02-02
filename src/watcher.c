/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucile <jlucile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:58:04 by jlucile           #+#    #+#             */
/*   Updated: 2021/11/17 16:58:05 by jlucile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	check_num_of_eat(t_param *params)
{
	int	i;
	int	ct;

	i = 0;
	ct = 0;
	while (i < params->num_of_philo)
	{
		if (params->philosophers->meals_count > params->num_of_eat)
			ct++;
		i++;
	}
	if (ct == params->num_of_philo)
		params->is_dead = 0;
}

void	watcher(t_param *params)
{
	int	i;

	while (params->is_dead)
	{
		i = 0;
		while (i < params->num_of_philo && params->is_dead)
		{
			pthread_mutex_lock(&params->eating);
			if (get_time() - params->start_time
				- params->philosophers[i].last_meal
				> params->time_to_die)
				print_death(i, params, "died");
			pthread_mutex_unlock(&params->eating);
			usleep(100);
			i++;
		}
		if (params->num_of_eat != -1 && params->is_dead)
			check_num_of_eat(params);
	}
}

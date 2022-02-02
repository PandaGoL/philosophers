/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucile <jlucile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:58:00 by jlucile           #+#    #+#             */
/*   Updated: 2021/11/17 16:58:02 by jlucile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	philo_eat(t_philosopher *philo)
{
	pthread_mutex_lock(philo->left);
	print_activ(philo->id, philo->params, "has taken left fork");
	pthread_mutex_lock(philo->right);
	print_activ(philo->id, philo->params, "has taken right fork");
	pthread_mutex_lock(&philo->params->eating);
	print_activ(philo->id, philo->params, "is eating");
	philo->last_meal = get_time() - philo->params->start_time;
	pthread_mutex_unlock(&philo->params->eating);
	usleep(philo->params->time_to_eat * 1000);
	philo->meals_count++;
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}

void	*philo_life(void *args)
{
	t_philosopher	*philo;
	t_param			*params;

	philo = (t_philosopher *) args;
	params = philo->params;
	if (philo->id % 2)
		usleep(20000);
	while (params->is_dead)
	{
		philo_eat(philo);
		print_activ(philo->id, params, "is sleeping");
		usleep(params->time_to_sleep * 1000);
		print_activ(philo->id, params, "is thinking");
	}
	return (NULL);
}

void	end_simulate(t_param *params)
{
	int	i;

	i = 0;
	while (i < params->num_of_philo)
	{
		pthread_join(params->philosophers[i].thread_philo, NULL);
		i++;
	}
	i = 0;
	while (i < params->num_of_philo)
	{
		pthread_mutex_destroy(&params->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&params->eating);
	pthread_mutex_destroy(&params->printing);
	free(params->forks);
	free(params->philosophers);
}

int	simulate(t_param *params)
{
	int				i;
	t_philosopher	*philo;

	i = 0;
	philo = params->philosophers;
	params->start_time = get_time();
	while (i < params->num_of_philo)
	{
		if (pthread_create(&philo[i].thread_philo, NULL, philo_life, &philo[i]))
			return (ft_perror(3));
		i++;
	}
	watcher(params);
	end_simulate(params);
	return (0);
}

int	main(int argc, char **argv)
{
	t_param		params;

	if (get_params(argc, argv, &params))
		return (1);
	if (init_mutex(&params))
		return (1);
	if (init_philo(&params))
		return (1);
	if (simulate(&params))
		return (1);
	return (0);
}

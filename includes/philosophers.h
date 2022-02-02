/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucile <jlucile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:58:18 by jlucile           #+#    #+#             */
/*   Updated: 2021/11/17 16:58:19 by jlucile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

struct s_param;

typedef struct s_philoshpher
{
	int 			id;
	int 			meals_count;
	long 			last_meal;
	pthread_mutex_t *left;
	pthread_mutex_t *right;
	pthread_t 		thread_philo;
	struct s_param 	*params;
}		t_philosopher;

typedef struct s_param
{
	int 			num_of_philo;
	int 			time_to_die;
	int 			time_to_eat;
	int 			time_to_sleep;
	int 			num_of_eat;
	int 			is_dead;
	long 			start_time;
	pthread_mutex_t *forks;
	pthread_mutex_t eating;
	pthread_mutex_t printing;
	t_philosopher	*philosophers;
}		t_param;

int		ft_atoi(const char *str);
int		ft_perror(int err);
long	get_time();
int		get_params(int argc, char **argv, t_param *params);
int 	init_mutex(t_param *param);
int		init_philo(t_param *params);
void	print_activ(int id, t_param *param, char *str);
void	print_death(int id, t_param *param, char *str);
void	watcher(t_param *params);
void	check_num_of_eat(t_param *params);

#endif

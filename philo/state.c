/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:05:16 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/13 12:04:15 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	check_is_one_dead(t_philosopher *philosopher)
{
	t_bool	is_one_dead;

	pthread_mutex_lock(&(philosopher->program->is_one_dead_mutex));
	is_one_dead = philosopher->program->is_one_dead;
	pthread_mutex_unlock(&(philosopher->program->is_one_dead_mutex));
	return (is_one_dead);
}

t_bool	check_is_dead(t_philosopher *philosopher)
{
	long	now;

	if (philosopher->state == DEAD)
		return (TRUE);
	now = get_timestamp_from_start(philosopher->program->start_timestamp);
	if (now - philosopher->last_meal_timestamp
		> philosopher->program->time_to_die)
	{
		philosopher->state = DEAD;
		pthread_mutex_lock(&(philosopher->program->is_one_dead_mutex));
		philosopher->program->is_one_dead = TRUE;
		pthread_mutex_unlock(&(philosopher->program->is_one_dead_mutex));
		ft_log(philosopher, "died");
		return (TRUE);
	}
	return (FALSE);
}

t_bool	should_stop(t_philosopher *philosophers, t_program *program)
{
	int		i;
	t_bool	all_eat;

	pthread_mutex_lock(&program->is_one_dead_mutex);
	if (program->is_one_dead)
		return (TRUE);
	pthread_mutex_unlock(&program->is_one_dead_mutex);
	i = 0;
	all_eat = TRUE;
	while (i < program->n_philosopher)
	{
		if (philosophers[i].eat_count < program->n_must_eat)
		{
			all_eat = FALSE;
			break ;
		}
		i++;
	}
	if (program->n_must_eat != -1 && all_eat)
		return (TRUE);
	return (FALSE);
}

t_bool	should_start(t_philosopher *philosophers, t_program *program)
{
	int		i;

	i = 0;
	while (i < program->n_philosopher)
	{
		if (philosophers[i].state == WAITING)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

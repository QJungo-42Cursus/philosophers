/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:05:16 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/19 13:42:06 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	check_is_dead(t_philosopher *philosopher)
{
	long	now;

	if (get_integer_mutexed(philosopher->state) == DEAD)
		return (TRUE);
	now = get_timestamp_from_start(get_long_mutexed(
				philosopher->program->start_timestamp));
	if (now - philosopher->last_meal_timestamp
		> philosopher->program->time_to_die)
	{
		set_integer_mutexed(philosopher->state, DEAD);
		set_boolean_mutexed(philosopher->program->is_one_dead, TRUE);
		ft_log(philosopher, "died");
		return (TRUE);
	}
	return (FALSE);
}

t_bool	should_stop(t_philosopher *philosophers, t_program *program)
{
	int		i;

	i = 0;
	while (i < program->n_philosopher)
	{
		if (get_integer_mutexed(philosophers[i].state) != GONE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_bool	should_start(t_philosopher *philosophers, t_program *program)
{
	int		i;

	i = 0;
	while (i < program->n_philosopher)
	{
		if (get_integer_mutexed(philosophers[i].state) != READY)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

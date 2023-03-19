/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:04:26 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/19 13:38:35 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philosophers.h"
#include <unistd.h>

static void	init_routine(t_philosopher **philosopher, void *philosopher_ptr)
{
	*philosopher = (t_philosopher *)philosopher_ptr;
	(*philosopher)->last_meal_timestamp = 0;
	set_integer_mutexed((*philosopher)->eat_count, 0);
	while (get_long_mutexed((*philosopher)->program->start_timestamp) == 0)
		(void)0;
}

static void	eat(t_philosopher *philosopher)
{
	int		eat_count;

	ft_log(philosopher, "is eating");
	philosopher->last_meal_timestamp = get_timestamp_from_start(
			get_long_mutexed(philosopher->program->start_timestamp));
	eat_count = get_integer_mutexed(philosopher->eat_count);
	set_integer_mutexed(philosopher->eat_count, eat_count + 1);
	custom_sleep(philosopher->program->time_to_eat, philosopher->program);
	drop_forks(philosopher);
}

void	*philosopher_routine(void *philosopher_ptr)
{
	t_philosopher	*philosopher;

	init_routine(&philosopher, philosopher_ptr);
	while (!check_is_dead(philosopher)
		&& !get_boolean_mutexed(philosopher->program->is_one_dead))
	{
		take_forks(philosopher);
		if (check_is_dead(philosopher)
			|| get_boolean_mutexed(philosopher->program->is_one_dead))
			break ;
		eat(philosopher);
		if (check_is_dead(philosopher)
			|| get_boolean_mutexed(philosopher->program->is_one_dead))
			break ;
		ft_log(philosopher, "is sleeping");
		custom_sleep(philosopher->program->time_to_sleep, philosopher->program);
		ft_log(philosopher, "is thinking");
		if (philosopher->program->n_must_eat != -1
			&& get_integer_mutexed(philosopher->eat_count)
			== philosopher->program->n_must_eat)
			break ;
	}
	set_integer_mutexed(philosopher->state, GONE);
	return (NULL);
}

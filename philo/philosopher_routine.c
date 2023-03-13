/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:04:26 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/13 11:16:49 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philosophers.h"
#include <unistd.h>

static void	init_routine(t_philosopher **philosopher, void *philosopher_ptr)
{
	*philosopher = (t_philosopher *)philosopher_ptr;
	(*philosopher)->state = READY;
	(*philosopher)->last_meal_timestamp = 0;
	(*philosopher)->eat_count = 0;
	while ((*philosopher)->program->start_timestamp == 0)
		usleep(1);
	ft_log(*philosopher, "wakes up");
}

static void	eat(t_philosopher *philosopher)
{
	ft_log(philosopher, "is eating");
	philosopher->last_meal_timestamp
		= get_timestamp_from_start(philosopher->program->start_timestamp);
	philosopher->eat_count++;
	custom_sleep(philosopher->program->time_to_eat, philosopher->program);
	drop_forks(philosopher);
}

void	*philosopher_routine(void *philosopher_ptr)
{
	t_philosopher	*philosopher;

	init_routine(&philosopher, philosopher_ptr);
	while (!check_is_dead(philosopher) && !check_is_one_dead(philosopher))
	{
		take_forks(philosopher);
		if (check_is_dead(philosopher) || check_is_one_dead(philosopher))
			break ;
		eat(philosopher);
		if (check_is_dead(philosopher) || check_is_one_dead(philosopher))
			break ;
		ft_log(philosopher, "is thinking");
		if (philosopher->program->n_must_eat != -1
			&& philosopher->eat_count == philosopher->program->n_must_eat)
			break ;
		ft_log(philosopher, "is sleeping");
		custom_sleep(philosopher->program->time_to_sleep, philosopher->program);
	}
	return (NULL);
}

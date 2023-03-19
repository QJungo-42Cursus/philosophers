/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:04:10 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/19 13:56:03 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "philosophers.h"

static int	init_program(t_program *program)
{
	if (pthread_mutex_init(&program->print_mutex, NULL) != SUCCESS)
		return (ERROR);
	program->is_one_dead = init_mutexed();
	if (program->is_one_dead == NULL)
	{
		pthread_mutex_destroy(&program->print_mutex);
		return (ERROR);
	}
	set_boolean_mutexed(program->is_one_dead, FALSE);
	program->start_timestamp = init_mutexed();
	if (program->start_timestamp == NULL)
	{
		pthread_mutex_destroy(&program->print_mutex);
		free_mutexed(program->is_one_dead);
		return (ERROR);
	}
	set_long_mutexed(program->start_timestamp, 0);
	return (SUCCESS);
}

static int	init_forks(t_mutexed ***forks, t_program *program)
{
	int		i;

	*forks = malloc(sizeof(t_mutexed *) * program->n_philosopher);
	if (*forks == NULL)
		return (ERROR);
	i = 0;
	while (i < program->n_philosopher)
	{
		(*forks)[i] = init_mutexed();
		if ((*forks)[i] == NULL)
		{
			free(*forks);
			return (ERROR);
		}
		set_boolean_mutexed((*forks)[i], FALSE);
		i++;
	}
	return (SUCCESS);
}

static int	init_philosophers_norm(t_philosopher *philosopher,
		int i, t_mutexed **forks, t_program *program)
{
	int		fork_index;

	philosopher->state = init_mutexed();
	if (philosopher->state == NULL)
		return (ERROR);
	set_integer_mutexed(philosopher->state, WAITING);
	philosopher->eat_count = init_mutexed();
	if (philosopher->eat_count == NULL)
	{
		free_mutexed(philosopher->state);
		return (ERROR);
	}
	set_integer_mutexed(philosopher->eat_count, 0);
	philosopher->left_fork = forks[i];
	if (i == 0)
		fork_index = program->n_philosopher - 1;
	else
		fork_index = i - 1;
	philosopher->right_fork = forks[fork_index];
	return (SUCCESS);
}

static int	init_philosophers(t_philosopher **philosophers,
		t_program *program, t_mutexed **forks, int i)
{
	*philosophers = malloc(sizeof(t_philosopher) * program->n_philosopher);
	if (*philosophers == NULL)
		return (ERROR);
	while (i < program->n_philosopher)
	{
		(*philosophers)[i].index = i;
		(*philosophers)[i].program = program;
		if (init_philosophers_norm(&(*philosophers)[i], i,
			forks, program) == ERROR)
		{
			free(*philosophers);
			return (ERROR);
		}
		if (pthread_create(&(*philosophers)[i].thread,
			NULL, &philosopher_routine, &(*philosophers)[i]) != SUCCESS)
		{
			free(*philosophers);
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

int	init_all(t_program *program, t_philosopher **philosophers,
		t_mutexed ***forks)
{
	if (init_program(program) == ERROR)
		return (ERROR);
	if (init_forks(forks, program) == ERROR)
	{
		pthread_mutex_destroy(&program->print_mutex);
		free_mutexed(program->is_one_dead);
		free_mutexed(program->start_timestamp);
		return (ERROR);
	}
	if (init_philosophers(philosophers, program, *forks, 0) == ERROR)
	{
		pthread_mutex_destroy(&program->print_mutex);
		free_mutexed(program->is_one_dead);
		free_mutexed(program->start_timestamp);
		free_forks(*forks, program);
		return (ERROR);
	}
	return (SUCCESS);
}

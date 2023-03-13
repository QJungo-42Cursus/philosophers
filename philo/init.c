/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:04:10 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/13 12:00:51 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "philosophers.h"

int	init_program(t_program *program)
{
	if (pthread_mutex_init(&program->print_mutex, NULL) != SUCCESS)
		return (ERROR);
	program->is_one_dead = FALSE;
	if (pthread_mutex_init(&program->is_one_dead_mutex, NULL) != SUCCESS)
	{
		pthread_mutex_destroy(&program->print_mutex);
		return (ERROR);
	}
	program->start_timestamp = 0;
	return (SUCCESS);
}

int	init_forks(t_fork **forks, t_program *program)
{
	int	i;

	*forks = malloc(sizeof(t_fork) * program->n_philosopher);
	if (*forks == NULL)
		return (ERROR);
	i = 0;
	while (i < program->n_philosopher)
	{
		(*forks)[i].index = i;
		(*forks)[i].is_used = FALSE;
		if (pthread_mutex_init(&(*forks)[i].mutex, NULL) != SUCCESS)
		{
			free(*forks);
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

static int	set_fork_index(int index, t_program *program)
{
	if (index == 0)
		return (program->n_philosopher - 1);
	return (index - 1);
}

int	init_philosophers(t_philosopher **philosophers,
		t_program *program, t_fork *forks)
{
	int		i;

	*philosophers = malloc(sizeof(t_philosopher) * program->n_philosopher);
	if (*philosophers == NULL)
		return (ERROR);
	i = 0;
	while (i < program->n_philosopher)
	{
		(*philosophers)[i].index = i;
		(*philosophers)[i].program = program;
		(*philosophers)[i].left_fork = &(forks[i]);
		(*philosophers)[i].right_fork = &(forks[set_fork_index(i, program)]);
		(*philosophers)[i].state = WAITING;
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
		t_fork **forks)
{
	if (init_program(program) == ERROR)
		return (ERROR);
	if (init_forks(forks, program) == ERROR)
	{
		pthread_mutex_destroy(&program->is_one_dead_mutex);
		pthread_mutex_destroy(&program->print_mutex);
		return (ERROR);
	}
	if (init_philosophers(philosophers, program, *forks) == ERROR)
	{
		pthread_mutex_destroy(&program->is_one_dead_mutex);
		pthread_mutex_destroy(&program->print_mutex);
		free_forks(*forks, program);
		return (ERROR);
	}
	return (SUCCESS);
}

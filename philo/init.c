#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "philosophers.h"
#include "utils.h"

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
	program->start_timestamp = get_timestamp();
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
		if (pthread_mutex_init(&(*forks)[i].mutex, NULL) != SUCCESS)
		{
			free(*forks);
			return (ERROR);
		}
		(*forks)[i].index = i;
		(*forks)[i].is_used = FALSE;
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
		if (pthread_create(&(*philosophers)[i].thread,
			NULL, &philosopher_routine, &(*philosophers)[i]) != SUCCESS)
		{
			free(*philosophers);
			return (ERROR);
		}
		(*philosophers)[i].index = i;
		(*philosophers)[i].program = program;
		(*philosophers)[i].left_fork = &(forks[i]);
		(*philosophers)[i].right_fork = &(forks[set_fork_index(i, program)]);
		i++;
	}
	return (SUCCESS);
}

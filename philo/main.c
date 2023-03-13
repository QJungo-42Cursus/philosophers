/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:03:39 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/13 11:26:46 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "philosophers.h"

#define INV_TIME_TO_DIE "Time to die must be an integer greater than 0\n"
#define INV_TIME_TO_EAT "Time to eat must be an integer greater than 0\n"
#define INV_TIME_TO_SLEEP "Time to sleep must be an integer greater than 0\n"
#define INV_N_OF_PHIL "N of philosophers must be an integer greater than 0\n"
#define INV_MUST_EAT "times each phil. must eat must be an integer > 0\n"

static int	return_print_error(char *str)
{
	printf("%s", str);
	return (ERROR);
}

static int	parse_args_set_program(int argc, char **argv, t_program *program)
{
	argv++;
	argc--;
	if (argc < 4 || 5 < argc)
	{
		printf("You have entered %d arguments instead of 4 or 5\n", argc);
		return (ERROR);
	}
	program->n_philosopher = ft_atoi(argv[0]);
	if (program->n_philosopher <= 0)
		return (return_print_error(INV_N_OF_PHIL));
	program->time_to_die = ft_atoi(argv[1]);
	if (program->time_to_die <= 0)
		return (return_print_error(INV_TIME_TO_DIE));
	program->time_to_eat = ft_atoi(argv[2]);
	if (program->time_to_eat <= 0)
		return (return_print_error(INV_TIME_TO_EAT));
	program->time_to_sleep = ft_atoi(argv[3]);
	if (program->time_to_sleep <= 0)
		return (return_print_error(INV_TIME_TO_SLEEP));
	program->n_must_eat = -1;
	if (argc == 5 && ft_atoi(argv[4]) <= 0)
		return (return_print_error(INV_MUST_EAT));
	if (argc == 5)
		program->n_must_eat = ft_atoi(argv[4]);
	return (SUCCESS);
}

static int	init_all(t_program *program, t_philosopher **philosophers,
		t_fork **forks	)
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

static int	run(t_program *program, t_philosopher *philosophers)
{
	int		i;

	i = 0;
	while (i < program->n_philosopher)
	{
		if (pthread_detach(philosophers[i].thread) != 0)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
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

static t_bool	should_start(t_philosopher *philosophers, t_program *program)
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

int	main(int argc, char **argv)
{
	t_program		program;
	t_philosopher	*philosophers;
	t_fork			*forks;

	if (parse_args_set_program(argc, argv, &program) == ERROR)
		return (ERROR);
	if (program.n_philosopher == 1)
	{
		usleep(program.time_to_die * 1000);
		printf("%06d 1 died\n", program.time_to_die);
		return (SUCCESS);
	}
	init_all(&program, &philosophers, &forks);
	if (run(&program, philosophers) == ERROR)
	{
		free(philosophers);
		return (ERROR);
	}
	while (!should_start(philosophers, &program))
		usleep(100);
	program.start_timestamp = get_timestamp();
	while (!should_stop(philosophers, &program))
		usleep(100);
	return (SUCCESS);
}

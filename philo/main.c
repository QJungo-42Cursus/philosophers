








#include "philosophers.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define INV_TIME_TO_DIE "Time to die must be an integer greater than 0\n"
#define INV_TIME_TO_EAT "Time to eat must be an integer greater than 0\n"
#define INV_TIME_TO_SLEEP "Time to sleep must be an integer greater than 0\n"
#define INV_N_OF_PHIL "N of philosophers must be an integer greater than 0\n"
#define INV_MUST_EAT "times each phil. must eat must be an integer > 0\n"

int	ft_atoi(const char *str);

int	return_print_error(char *str)
{
	printf("%s", str);
	return (ERROR);
}

static int	parse_args_set_program(int argc, char **argv, t_program *program)
{
	program->n_philosopher = ft_atoi(argv[0]);
	if (program->n_philosopher <= 0)
		return return_print_error(INV_N_OF_PHIL);
	program->time_to_die = ft_atoi(argv[1]);
	if (program->time_to_die <= 0)
		return return_print_error(INV_TIME_TO_DIE);
	if (program->n_philosopher == 1) // TODO + clean ??
	{
		usleep(program->time_to_die * 1000);
		printf("%06d 1 died\n", program->time_to_die);
		return (SUCCESS);
	}
	program->time_to_eat = ft_atoi(argv[2]);
	if (program->time_to_eat <= 0)
		return return_print_error(INV_TIME_TO_EAT);
	program->time_to_sleep = ft_atoi(argv[3]);
	if (program->time_to_sleep <= 0)
		return return_print_error(INV_TIME_TO_SLEEP);
	program->must_eat = -1;
	if (argc == 5 && ft_atoi(argv[4]) <= 0)
		return return_print_error(INV_MUST_EAT);
	if (argc == 5)
		program->must_eat = ft_atoi(argv[4]);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_program		program;
	t_philosopher	*philosophers;
	//pthread_t		*threads;

	argv++;
	argc--;
	if (argc < 4 || 5 < argc)
	{
		printf("You have entered %d arguments instead of 4 or 5\n", argc);
		return (1);
	}
	parse_args_set_program(argc, argv, &program);

//	init_shared_mutex_infos(&program);
//	philosophers = init_philosophers(program);

	threads = malloc(sizeof(pthread_t) * program.n_philosopher);
	if (threads == NULL)
	{
		free_shared_mutex(program);
		free(philosophers);
		printf(MSG_ERR_THREADS_MALLOC);
		return (ERROR);
	}
	start_threads(program, philosophers, threads);
	free_all(program, philosophers, threads, NULL);
}

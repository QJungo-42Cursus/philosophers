#include "philosophers.h"
#include <stdlib.h>

void	free_forks(t_fork *forks, t_program *program)
{
	int	i;

	i = 0;
	while (i < program->n_philosopher)
	{
		pthread_mutex_destroy(&forks[i].mutex);
		i++;
	}
	free(forks);
}

void	free_philosophers(t_philosopher *philosophers, t_program *program)
{
	int	i;

	i = 0;
	while (i < program->n_philosopher)
	{
		// TODO
		//pthread_join(philosophers[i].thread, NULL);
		i++;
	}
	free(philosophers);
}

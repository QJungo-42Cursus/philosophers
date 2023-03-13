#include "philosophers.h"

t_bool	check_is_one_dead(t_philosopher *philosopher)
{
	t_bool	is_one_dead;

	pthread_mutex_lock(&(philosopher->program->is_one_dead_mutex));
	is_one_dead = philosopher->program->is_one_dead;
	pthread_mutex_unlock(&(philosopher->program->is_one_dead_mutex));
	return (is_one_dead);
}


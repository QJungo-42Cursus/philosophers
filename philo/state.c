#include "philosophers.h"

t_bool	check_is_one_dead(t_philosopher *philosopher)
{
	t_bool	is_one_dead;

	pthread_mutex_lock(&(philosopher->program->is_one_dead_mutex));
	is_one_dead = philosopher->program->is_one_dead;
	pthread_mutex_unlock(&(philosopher->program->is_one_dead_mutex));
	return (is_one_dead);
}

t_bool	check_is_dead(t_philosopher *philosopher)
{
	long	now;

	if (philosopher->state == DEAD)
		return (TRUE);
	now = get_timestamp_from_start(philosopher->program->start_timestamp);
	if (now - philosopher->last_meal_timestamp > philosopher->program->time_to_die)
	{
		philosopher->state = DEAD;
		pthread_mutex_lock(&(philosopher->program->is_one_dead_mutex));
		philosopher->program->is_one_dead = TRUE;
		pthread_mutex_unlock(&(philosopher->program->is_one_dead_mutex));
		ft_log(philosopher, "died");
		return (TRUE);
	}
	return (FALSE);
}

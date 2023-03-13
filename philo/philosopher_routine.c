#include <stdio.h>
#include "philosophers.h"
#include <unistd.h>

static void	init_routine(t_philosopher **philosopher, void *philosopher_ptr)
{
	*philosopher = (t_philosopher *)philosopher_ptr;
	(*philosopher)->state = SLEEPING;
	(*philosopher)->last_meal_timestamp = 0;
	(*philosopher)->eat_count = 0;
	ft_log(*philosopher, "wakes up");
}

static t_bool am_i_dead(t_philosopher *philosopher)
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
		// printf im dead TODO
		return (TRUE);
	}
	return (FALSE);
}

static void	take_forks(t_philosopher *philosopher)
{
	while (TRUE)
	{
		if (am_i_dead(philosopher) || check_is_one_dead(philosopher) == TRUE)
			return ;
		pthread_mutex_lock(&(philosopher->left_fork->mutex));
		if (philosopher->left_fork->is_used == TRUE)
		{
			pthread_mutex_unlock(&(philosopher->left_fork->mutex));
			usleep(10);
			continue ;
		}
		else
		{
			philosopher->left_fork->is_used = TRUE;
			pthread_mutex_unlock(&(philosopher->left_fork->mutex));
			ft_log(philosopher, "has taken a fork");
			break ;
		}
	}
	while (TRUE)
	{
		if (am_i_dead(philosopher) || check_is_one_dead(philosopher) == TRUE)
			return ;
		pthread_mutex_lock(&(philosopher->right_fork->mutex));
		if (philosopher->right_fork->is_used == TRUE)
		{
			pthread_mutex_unlock(&(philosopher->right_fork->mutex));
			usleep(10);
			continue ;
		}
		else
		{
			philosopher->right_fork->is_used = TRUE;
			pthread_mutex_unlock(&(philosopher->right_fork->mutex));
			ft_log(philosopher, "has taken a fork");
			break ;
		}
	}
}

static void drop_forks(t_philosopher *philosopher)
{
	pthread_mutex_lock(&(philosopher->left_fork->mutex));
	pthread_mutex_lock(&(philosopher->right_fork->mutex));
	philosopher->left_fork->is_used = FALSE;
	philosopher->right_fork->is_used = FALSE;
	pthread_mutex_unlock(&(philosopher->left_fork->mutex));
	pthread_mutex_unlock(&(philosopher->right_fork->mutex));
}

void	eat(t_philosopher *philosopher)
{
	philosopher->state = EATING;
	ft_log(philosopher, "is eating");
	philosopher->last_meal_timestamp = get_timestamp_from_start(philosopher->program->start_timestamp);
	philosopher->eat_count++;
	custom_sleep(philosopher->program->time_to_eat, philosopher->program);
	drop_forks(philosopher);
}

void	think(t_philosopher *philosopher)
{
	philosopher->state = THINKING;
	ft_log(philosopher, "is thinking");
}

void	sleep_(t_philosopher *philosopher)
{
	philosopher->state = SLEEPING;
	ft_log(philosopher, "is sleeping");
	custom_sleep(philosopher->program->time_to_sleep, philosopher->program);
}

void	*philosopher_routine(void *philosopher_ptr)
{
	t_philosopher	*philosopher;

	init_routine(&philosopher, philosopher_ptr);
	while (!am_i_dead(philosopher) && !check_is_one_dead(philosopher))
	{
		take_forks(philosopher);
		if (am_i_dead(philosopher) || check_is_one_dead(philosopher))
			break ;
		eat(philosopher);
		if (am_i_dead(philosopher) || check_is_one_dead(philosopher))
			break ;
		think(philosopher);
		if (philosopher->program->n_must_eat != -1
			&& philosopher->eat_count == philosopher->program->n_must_eat)
			break ;
		sleep_(philosopher);
	}
	return (NULL);
}

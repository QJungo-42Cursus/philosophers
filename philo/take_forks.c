#include "philosophers.h"
#include <unistd.h>
#define WAITING_TIME 10

static int take_one_fork(t_fork *fork)
{
	pthread_mutex_lock(&(fork->mutex));
	if (fork->is_used == TRUE)
	{
		pthread_mutex_unlock(&(fork->mutex));
		return (FALSE);
	}
	fork->is_used = TRUE;
	pthread_mutex_unlock(&(fork->mutex));
	return (TRUE);
}

void	take_forks(t_philosopher *philosopher)
{
	t_fork	*first_fork;
	t_fork	*second_fork;

	if (philosopher->index % 2 == 0)
	{
		first_fork = philosopher->left_fork;
		second_fork = philosopher->right_fork;
	}
	else
	{
		first_fork = philosopher->right_fork;
		second_fork = philosopher->left_fork;
	}

	while (TRUE)
	{
		if (check_is_dead(philosopher) || check_is_one_dead(philosopher) == TRUE)
			return ;
		if (take_one_fork(first_fork))
		{
			ft_log(philosopher, "has taken a fork");
			break ;
		}
		usleep(WAITING_TIME);
	}
	while (TRUE)
	{
		if (check_is_dead(philosopher) || check_is_one_dead(philosopher) == TRUE)
			return ;
		if (take_one_fork(second_fork))
		{
			ft_log(philosopher, "has taken a fork");
			break ;
		}
		usleep(WAITING_TIME);
	}
}

void	drop_forks(t_philosopher *philosopher)
{
	pthread_mutex_lock(&(philosopher->left_fork->mutex));
	pthread_mutex_lock(&(philosopher->right_fork->mutex));
	philosopher->left_fork->is_used = FALSE;
	philosopher->right_fork->is_used = FALSE;
	pthread_mutex_unlock(&(philosopher->left_fork->mutex));
	pthread_mutex_unlock(&(philosopher->right_fork->mutex));
}


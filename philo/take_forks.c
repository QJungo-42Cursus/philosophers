/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:05:22 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/13 10:10:54 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#define WAITING_TIME 10

static int	take_one_fork(t_fork *fork)
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

static void	wait_to_take_one_fork(t_fork *fork, t_philosopher *philosopher)
{
	while (TRUE)
	{
		if (check_is_dead(philosopher) || check_is_one_dead(philosopher))
			return ;
		if (take_one_fork(fork))
		{
			ft_log(philosopher, "has taken a fork");
			break ;
		}
		usleep(WAITING_TIME);
	}
}

void	take_forks(t_philosopher *philosopher)
{
	t_fork	*first_fork;
	t_fork	*second_fork;

	first_fork = philosopher->right_fork;
	second_fork = philosopher->left_fork;
	if (philosopher->index % 2 == 0)
	{
		first_fork = philosopher->left_fork;
		second_fork = philosopher->right_fork;
	}
	wait_to_take_one_fork(first_fork, philosopher);
	if (check_is_dead(philosopher) || check_is_one_dead(philosopher))
		return ;
	wait_to_take_one_fork(second_fork, philosopher);
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

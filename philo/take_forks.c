/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:05:22 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/19 12:14:22 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#define WAITING_TIME 10

static int	take_one_fork(t_mutexed *fork)
{
	t_bool	is_used;

	is_used = get_boolean_mutexed(fork);
	if (is_used)
		return (FALSE);
	set_boolean_mutexed(fork, TRUE);
	return (TRUE);
}

static void	wait_to_take_one_fork(t_mutexed *fork, t_philosopher *philosopher)
{
	while (TRUE)
	{
		if (check_is_dead(philosopher) || get_boolean_mutexed(
				philosopher->program->is_one_dead))
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
	t_mutexed	*first_fork;
	t_mutexed	*second_fork;

	first_fork = philosopher->right_fork;
	second_fork = philosopher->left_fork;
	if (philosopher->index % 2 == 0)
	{
		first_fork = philosopher->left_fork;
		second_fork = philosopher->right_fork;
	}
	wait_to_take_one_fork(first_fork, philosopher);
	if (check_is_dead(philosopher) || get_boolean_mutexed(
			philosopher->program->is_one_dead))
		return ;
	wait_to_take_one_fork(second_fork, philosopher);
}

void	drop_forks(t_philosopher *philosopher)
{
	set_boolean_mutexed(philosopher->left_fork, FALSE);
	set_boolean_mutexed(philosopher->right_fork, FALSE);
}

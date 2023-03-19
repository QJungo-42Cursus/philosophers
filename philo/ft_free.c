/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:03:57 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/19 13:26:58 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <stdlib.h>

void	free_mutexed(t_mutexed *mutexed)
{
	pthread_mutex_destroy(&mutexed->mutex);
	free(mutexed);
}

void	free_forks(t_mutexed **forks, t_program *program)
{
	int	i;

	i = 0;
	while (i < program->n_philosopher)
	{
		free_mutexed(forks[i]);
		i++;
	}
	free(forks);
}

void	free_all(t_mutexed **forks,
		t_program *program, t_philosopher *philosophers)
{
	int		i;

	usleep(1000);
	i = 0;
	while (i < program->n_philosopher)
	{
		free_mutexed(philosophers[i].state);
		free_mutexed(philosophers[i].eat_count);
		i++;
	}
	free(philosophers);
	free_mutexed(program->is_one_dead);
	free_mutexed(program->start_timestamp);
	free_forks(forks, program);
	pthread_mutex_destroy(&program->print_mutex);
}

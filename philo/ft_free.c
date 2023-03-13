/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:03:57 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/13 12:09:45 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
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

void	free_all(t_fork *forks, t_program *program, t_philosopher *philosophers)
{
	usleep(1000);
	pthread_mutex_destroy(&program->print_mutex);
	pthread_mutex_destroy(&program->is_one_dead_mutex);
	free_forks(forks, program);
	free(philosophers);
}

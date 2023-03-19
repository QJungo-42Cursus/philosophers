/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexed_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 13:27:27 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/19 13:27:28 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philosophers.h"

void	*get_pointer_mutexed(t_mutexed *mutexed)
{
	void	*value;

	pthread_mutex_lock(&mutexed->mutex);
	value = mutexed->pointer;
	pthread_mutex_unlock(&mutexed->mutex);
	return (value);
}

void	set_pointer_mutexed(t_mutexed *mutexed, void *value)
{
	pthread_mutex_lock(&mutexed->mutex);
	mutexed->pointer = value;
	pthread_mutex_unlock(&mutexed->mutex);
}

long	get_long_mutexed(t_mutexed *mutexed)
{
	long	value;

	pthread_mutex_lock(&mutexed->mutex);
	value = mutexed->long_integer;
	pthread_mutex_unlock(&mutexed->mutex);
	return (value);
}

void	set_long_mutexed(t_mutexed *mutexed, long value)
{
	pthread_mutex_lock(&mutexed->mutex);
	mutexed->long_integer = value;
	pthread_mutex_unlock(&mutexed->mutex);
}

t_mutexed	*init_mutexed(void)
{
	t_mutexed	*mutexed;

	mutexed = malloc(sizeof(t_mutexed));
	if (!mutexed)
		return (NULL);
	mutexed->long_integer = 0;
	if (pthread_mutex_init(&mutexed->mutex, NULL) != SUCCESS)
	{
		free(mutexed);
		return (NULL);
	}
	return (mutexed);
}

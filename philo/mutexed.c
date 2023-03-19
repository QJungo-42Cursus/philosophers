/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexed.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 13:26:48 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/19 13:26:49 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	get_boolean_mutexed(t_mutexed *mutexed)
{
	t_bool	value;

	pthread_mutex_lock(&mutexed->mutex);
	value = mutexed->boolean;
	pthread_mutex_unlock(&mutexed->mutex);
	return (value);
}

void	set_boolean_mutexed(t_mutexed *mutexed, t_bool value)
{
	pthread_mutex_lock(&mutexed->mutex);
	mutexed->boolean = value;
	pthread_mutex_unlock(&mutexed->mutex);
}

int	get_integer_mutexed(t_mutexed *mutexed)
{
	int		value;

	pthread_mutex_lock(&mutexed->mutex);
	value = mutexed->integer;
	pthread_mutex_unlock(&mutexed->mutex);
	return (value);
}

void	set_integer_mutexed(t_mutexed *mutexed, int value)
{
	pthread_mutex_lock(&mutexed->mutex);
	mutexed->integer = value;
	pthread_mutex_unlock(&mutexed->mutex);
}

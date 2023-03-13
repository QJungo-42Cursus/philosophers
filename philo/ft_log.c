/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:04:06 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/13 10:04:21 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

void	ft_log(t_philosopher *philosopher, char *msg)
{
	pthread_mutex_lock(&(philosopher->program->print_mutex));
	printf("%ld %d %s\n",
		get_timestamp_from_start(philosopher->program->start_timestamp),
		philosopher->index + 1, msg);
	pthread_mutex_unlock(&(philosopher->program->print_mutex));
}

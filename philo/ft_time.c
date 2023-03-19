/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:05:10 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/19 13:26:39 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include "philosophers.h"

long	get_timestamp(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == SUCCESS)
		return (time.tv_sec * 1000 + time.tv_usec / 1000);
	return (-1);
}

long	get_timestamp_from_start(long start)
{
	long	now;

	now = get_timestamp();
	if (now < 0)
		return (-1);
	return (now - start);
}

void	custom_sleep(long ms, t_program *program)
{
	long	start;
	long	now;

	start = get_timestamp_from_start(
			get_long_mutexed(program->start_timestamp));
	now = start;
	while (now < ms + start)
	{
		usleep(10);
		now = get_timestamp_from_start(
				get_long_mutexed(program->start_timestamp));
	}
}

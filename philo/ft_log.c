/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:04:06 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/13 14:38:48 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

static int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	while (((unsigned char)str1[i] || (unsigned char)str2[i]) && i < n)
	{
		if ((unsigned char)str1[i] > (unsigned char)str2[i])
			return (1);
		if ((unsigned char)str1[i] < (unsigned char)str2[i])
			return (-1);
		i++;
	}
	return (0);
}

void	ft_log(t_philosopher *philosopher, char *msg)
{
	static t_bool	one_died = FALSE;

	if (one_died)
		return ;
	one_died = (ft_strncmp(msg, "died", 5) == 0);
	pthread_mutex_lock(&(philosopher->program->print_mutex));
	printf("%ld %d %s\n",
		get_timestamp_from_start(philosopher->program->start_timestamp),
		philosopher->index + 1, msg);
	pthread_mutex_unlock(&(philosopher->program->print_mutex));
}

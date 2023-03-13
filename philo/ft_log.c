
/*
static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
*/

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

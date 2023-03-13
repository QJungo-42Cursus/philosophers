/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:03:43 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/13 11:19:32 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>

typedef enum e_bool {
	FALSE,
	TRUE
}	t_bool;

enum e_success {
	SUCCESS,
	ERROR,
};

typedef struct e_program {
	int				n_philosopher;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_must_eat;
	pthread_mutex_t	is_one_dead_mutex;
	t_bool			is_one_dead;
	long			start_timestamp;
	pthread_mutex_t	print_mutex;
}	t_program;

typedef enum e_state {
	WAITING,
	READY,
	DEAD,
}	t_state;

typedef struct s_fork {
	int				index;
	pthread_mutex_t	mutex;
	t_bool			is_used;
}	t_fork;

typedef struct s_philosopher {
	int					index;
	t_state				state;
	long				last_meal_timestamp;
	int					eat_count;
	pthread_t			thread;
	t_program			*program;
	t_fork				*left_fork;
	t_fork				*right_fork;
}	t_philosopher;

// philosopher_routine.c
void	*philosopher_routine(void *philosopher_ptr);

// init.c
int		init_program(t_program *program);
int		init_forks(t_fork **forks, t_program *program);
int		init_philosophers(t_philosopher **philosophers,
			t_program *program, t_fork *forks);

// state.c
t_bool	check_is_one_dead(t_philosopher *philosopher);
t_bool	check_is_dead(t_philosopher *philosopher);

// ft_log
void	ft_log(t_philosopher *philosopher, char *msg);

// ft_free.c
void	free_forks(t_fork *forks, t_program *program);

// ft_atoi.c
int		ft_atoi(const char *str);

// ft_time.c
void	custom_sleep(long ms, t_program *program);
long	get_timestamp(void);
long	get_timestamp_from_start(long start);

// take_forks.c
void	take_forks(t_philosopher *philosopher);
void	drop_forks(t_philosopher *philosopher);

#endif /* PHILOSOPHERS_H */

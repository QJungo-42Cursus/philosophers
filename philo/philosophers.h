/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:03:43 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/19 13:32:42 by qjungo           ###   ########.fr       */
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

/****************************** mutexed */
typedef struct s_mutexed {
	pthread_mutex_t	mutex;
	union {
		void		*pointer;
		int			integer;
		t_bool		boolean;
		long		long_integer;
	};
}	t_mutexed;

void		set_long_mutexed(t_mutexed *mutexed, long value);
long		get_long_mutexed(t_mutexed *mutexed);
t_bool		get_boolean_mutexed(t_mutexed *mutexed);
void		set_boolean_mutexed(t_mutexed *mutexed, t_bool value);
int			get_integer_mutexed(t_mutexed *mutexed);
void		set_integer_mutexed(t_mutexed *mutexed, int value);
void		*get_pointer_mutexed(t_mutexed *mutexed);
void		set_pointer_mutexed(t_mutexed *mutexed, void *value);
t_mutexed	*init_mutexed(void);
/********************************************************************/

typedef struct e_program {
	int				n_philosopher;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_must_eat;
	pthread_mutex_t	print_mutex;
	t_mutexed		*is_one_dead;
	t_mutexed		*start_timestamp;
}	t_program;

typedef enum e_state {
	WAITING,
	READY,
	DEAD,
	GONE,
}	t_state;

typedef struct s_philosopher {
	int					index;
	long				last_meal_timestamp;
	pthread_t			thread;
	t_mutexed			*eat_count;
	t_mutexed			*state;
	t_program			*program;
	t_mutexed			*left_fork;
	t_mutexed			*right_fork;
}	t_philosopher;

// philosopher_routine.c
void		*philosopher_routine(void *philosopher_ptr);

// init.c
int			init_all(t_program *program, t_philosopher **philosophers,
				t_mutexed ***forks);

// state.c
//t_bool	check_is_one_dead(t_philosopher *philosopher);
t_bool		check_is_dead(t_philosopher *philosopher);
t_bool		should_stop(t_philosopher *philosophers, t_program *program);
t_bool		should_start(t_philosopher *philosophers, t_program *program);

// ft_log
void		ft_log(t_philosopher *philosopher, char *msg);

// ft_free.c
void		free_forks(t_mutexed **forks, t_program *program);
void		free_all(t_mutexed **forks, t_program *program,
				t_philosopher *philosophers);
void		free_mutexed(t_mutexed *mutexed);

// ft_atoi.c
int			ft_atoi(const char *str);

// ft_time.c
void		custom_sleep(long ms, t_program *program);
long		get_timestamp(void);
long		get_timestamp_from_start(long start);

// take_forks.c
void		take_forks(t_philosopher *philosopher);
void		drop_forks(t_philosopher *philosopher);

#endif /* PHILOSOPHERS_H */

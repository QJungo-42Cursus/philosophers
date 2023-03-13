#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

typedef enum e_bool {
	FALSE,
	TRUE
}	t_bool;

enum e_success {
	SUCCESS,
	ERROR,
};

typedef struct e_program {
	int		n_philosopher;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		must_eat;
}	t_program;

typedef enum e_state {
	EATING,
	THINKING,
	SLEEPING,
	//FORK,
	//DEAD
}	t_state;

typedef struct s_philosopher {
	t_state		state;
}	t_philosopher;

typedef struct s_fork {
	t_bool		is_used;
}	t_fork;

#endif /* PHILOSOPHERS_H */

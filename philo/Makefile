NAME =     		philo
CC =			gcc
CFLAGS =		-Wall -Wextra -Werror -pthread
RM =			rm -f

SRCS =			main.c \
				philosopher_routine.c \
				init.c \
				state.c \
				take_forks.c \
				ft_atoi.c \
				ft_time.c \
				ft_log.c \
				ft_free.c \


OBJS =			$(SRCS:.c=.o)

all: $(NAME)
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

### TESTS ###

# number_of_philosophers
# time_to_die
# time_to_eat
# time_to_sleep
# [number_of_times_each_philosopher_must_eat]
ARGS_DEAD = 3 2000 200 200
ARGS_NICE = 6 1000 200 200


d: all
	@echo -e "\n\033[1;31mDEAD $(ARGS_DEAD) \033[0m"
	@./$(NAME) $(ARGS_DEAD)

t: all
	@echo -e "Nice one : $(ARGS_NICE)\n\n" '\n'
	@./$(NAME) $(ARGS_NICE)

sl: all
	@echo -e "should live : 4 410 200 200\n\n" '\n'
	@./$(NAME) 4 410 200 200

sd: all
	@echo -e "should die : 4 310 200 100\n\n" '\n'
	@./$(NAME) 4 310 200 100

leaks: all
	@echo -e "Leaks : $(ARGS_DEAD)\n\n" '\n'
	leaks -atExit -- ./$(NAME) $(ARGS_NICE)
#@valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) $(ARGS_DEAD)

eval: all
	@echo -e "should just die : \n"
	@./$(NAME) 1 800 200 200
	@sleep 3
	@echo -e "should die \n"
	@./$(NAME) 4 310 200 200
	@sleep 3
	@echo -e "should live \n"
	@./$(NAME) 4 410 200 200
	@sleep 3

SAN =	-fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all \
		-fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow \
		-fno-sanitize=null -fno-sanitize=alignment

san:
	@echo -e "San : $(ARGS_DEAD)\n\n" '\n'
	@gcc -g $(SAN) $(SRCS) -o $(NAME)
	./$(NAME) $(ARGS_DEAD)
	./$(NAME) $(ARGS_NICE)


db:
	@$(CC) $(CFLAGS) -g $(SRCS) -o $(NAME)
	lldb ./$(NAME) 5 800 200 200 7
	#lldb ./$(NAME) $(ARGS_NICE) 3

.PHONY: all clean fclean re

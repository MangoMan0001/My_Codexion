# ==============================================================================
#                                 VARIABLES
# ==============================================================================
NAME 		= codexion

CC 			= cc
CFLAG   	= -Wall -Wextra -Werror -pthread $(INCLUDES)

# ------------------------------------------------------------------------------
#                                 SOURCE FILES
# ------------------------------------------------------------------------------
CODE_DIR	= coders

CODE_CORE	= main.c codexion.c init.c validate.c
CODE_SCHED	= scheduler.c heap.c
CODE_SIM	= routine.c simulation.c compile.c subroutine.c
CODE_UTILS	= clean.c time.c utils.c

INCLUDES 	= -I./coders/include

SRCS        = $(addprefix $(CODE_DIR)/core/, $(CODE_CORE)) \
			  $(addprefix $(CODE_DIR)/scheduler/, $(CODE_SCHED)) \
			  $(addprefix $(CODE_DIR)/simulation/, $(CODE_SIM)) \
			  $(addprefix $(CODE_DIR)/utils/, $(CODE_UTILS))

OBJS 		= $(SRCS:.c=.o)

# ==============================================================================
#                                   RULES
# ==============================================================================
all: $(NAME)

$(NAME): $(OBJS)
		@echo "----------------------------------------"
		@echo "         Conpiling $(NAME)..."
		@echo "----------------------------------------"
		@$(CC) $(CFLAG) $(OBJS) -o $(NAME)
		@echo "Done!"

%.o: %.c
		@$(CC) $(CFLAG) -c $< -o $@

val: re
		@make clean
		@valgrind --tool=helgrind -q ./codexion 5 910 200 200 200 7 100 fifo
# 		@valgrind --leak-check=full -q ./codexion 5 910 200 200 200 7 100 fifo

run: re
		@make clean
		@./codexion 2 910 200 200 200 5 100 fifo

clean:
		@echo "CLeaning..."
		@rm -f $(OBJS)

fclean: clean
		@echo "Full CLeaning..."
		@rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re force

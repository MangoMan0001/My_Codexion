# ==============================================================================
#                                 VARIABLES
# ==============================================================================
NAME = codexion

CC = cc
CFLAG   = -Wall -Wextra -Werror -pthread $(INCLUDES)

# ------------------------------------------------------------------------------
#                                 SOURCE FILES
# ------------------------------------------------------------------------------
SRC_DIR     = src

SRC_CORE    = main.c codexion.c init.c validate.c
SRC_SCHED   = scheduler.c fifo.c
SRC_SIM  = routine.c simulation.c compile.c subroutine.c
SRC_UTILS   = clean.c time.c utils.c

INCLUDES = -I./include

SRCS        = $(addprefix $(SRC_DIR)/core/, $(SRC_CORE)) \
			  $(addprefix $(SRC_DIR)/scheduler/, $(SRC_SCHED)) \
			  $(addprefix $(SRC_DIR)/simulation/, $(SRC_SIM)) \
			  $(addprefix $(SRC_DIR)/utils/, $(SRC_UTILS)) \

OBJS = $(SRCS:.c=.o)

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
		@valgrind --tool=helgrind -q ./codexion

# helgrind
run: re
		@make clean
		@./codexion 5 710 200 200 200 5 100 edf

clean:
		@echo "CLeaning..."
		@rm -f $(OBJS)

fclean: clean
		@echo "Full CLeaning..."
		@rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re force

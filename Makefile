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

SRC_MAIN    = main.c

# SRC_INIT    = init_data.c init_mutex.c parser.c
# SRC_THREAD  = routine.c actions.c monitor.c
# SRC_SCHED   = arbiter.c queue.c
# SRC_UTILS   = time.c output.c cleanup.c

INCLUDES = -I./include

SRCS        = $(addprefix $(SRC_DIR)/core/, $(SRC_MAIN)) \
            #   $(addprefix $(SRC_DIR)/init/, $(SRC_INIT)) \
            #   $(addprefix $(SRC_DIR)/thread/, $(SRC_THREAD)) \
            #   $(addprefix $(SRC_DIR)/scheduler/, $(SRC_SCHED)) \
            #   $(addprefix $(SRC_DIR)/utils/, $(SRC_UTILS))

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

clean:
		@echo "CLeaning..."
		@rm -f $(OBJS)

fclean: clean
		@echo "Full CLeaning..."
		@rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re force

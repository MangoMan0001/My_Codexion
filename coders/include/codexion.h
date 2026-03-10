/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhirose <ayhirose@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 19:17:39 by ayhirose          #+#    #+#             */
/*   Updated: 2026/03/10 11:39:17 by ayhirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# define _DEFAULT_SOURCE
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>
# include <stddef.h>
# include <limits.h>

// --- Constants ---
# define TRUE 1
# define FALSE 0
# define FIFO 1
# define EDF 2

// Error messages
# define ERR_ARGS "Error: Invalid arguments\n"
# define ERR_MALLOC "Error: Memory allocation failed\n"
# define ERR_THREAD "Error: Thread creation failed\n"

typedef struct s_rules	t_rules;

/*
** Individual coder structure
** Each thread manages its own state through this struct.
*/
typedef struct s_coder
{
	int				id; // Coder ID (1 to N)
	pthread_t		tid; // Thread ID
	// --- Coder info ---
	int				left_coder_id; // ID of the coder sitting on the left
	int				right_coder_id; // ID of the coder sitting on the right
	// --- Dongle info ---
	int				left_dongle_id; // Left dongle ID (array index)
	int				right_dongle_id; // Right dongle ID (array index)
	// --- State management ---
	int				compile_count; // Number of times compiled so far
	long long		last_compile_start; // last compile start (μs)
	long long		enqueue_time; // Time added to queue (μs)
	int				is_in_queue; // 1 if currently waiting in the queue
	// --- Reference to shared data ---
	t_rules			*rule; // Pointer to the parent (global rules)
}	t_coder;

/*
** Global rules and shared resources structure
** Created once in the main thread and referenced by all coders.
** All reads/writes must be protected through global_lock.
*/
struct s_rules
{
	// --- Configurations ---
	int				num_coders;
	long long		time_to_burnout; // Reference time (μs)
	long long		time_to_compile;
	long long		time_to_debug;
	long long		time_to_refactor;
	int				must_compile_count; // Target number of compiles
	int				dongle_cooldown; // Dongle cooldown time (μs)
	int				scheduler_type; // Scheduler type (FIFO or EDF)
	// --- Time management ---
	long long		start_time; // Simulation start timestamp
	// --- Control flags ---
	int				is_simulation_active; // 1: active, 0: finished
	int				finished_coders; // Number of coders who reached the target
	// --- Synchronization primitives ---
	pthread_mutex_t	global_lock; // Master lock for data and output protection
	pthread_cond_t	cond; // Condition variable for sleeping/waking threads
	// --- Shared resources (Dongles) ---
	pthread_mutex_t	*dongle_locks; // Mutex for each individual dongle
	long long		*dongle_cool_times; // Timestamp dongle
	int				*dongle_status; // 0: available, 1: in use
	// --- Waiting queue (Heap) ---
	int				*queue; // Array of waiting coder IDs
	int				queue_size; // Current number of coders in the queue
	// --- Child data ---
	t_coder			*coders; // Array of all coders
	// --- Monitor ---
	pthread_t		monitor; // Monitor thread ID
};

// Function prototypes

// core
int			codexion(int argc, char **argv);
int			validate(int argc, char **argv);
int			init(t_rules *rule, int argc, char **argv);

// scheduler
int			scheduler(t_coder *coder);
void		pop_queue(t_coder *coder);
void		shift_up(int n, t_rules *rule);
int			compare_coders(int id1, int id2, t_rules *rule);

// simulation
int			simulation(t_rules *rule);
void		*routine(void *arg);
void		routine_compile(t_coder *coder, int *flag);
void		*monitor(void *arg);

// utils
void		free_rule(t_rules *rule);
void		destroy_mutexes(t_rules *r);
int			just_sleep(long long time, t_rules *rules);
long long	get_time(void);
void		*my_calloc(size_t size);
void		print_log(t_coder *coder, long long now, char *msg);
void		print_log_lock(t_coder *coder, long long now, char *msg);

#endif

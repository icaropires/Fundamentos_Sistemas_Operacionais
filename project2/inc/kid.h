#ifndef PROJECT2_INC_KID_H_
#define PROJECT2_INC_KID_H_

#define _GNU_SOURCE
#define _BSD_SOURCE

#include <time.h>

#include "../inc/utils.h"
#include "../inc/semaphore.h"

// Messages.
#define CROSSING_MSG "Kid is crossing"
#define CROSSED_MSG "Kid has crossed"
#define THINKING_MSG "Kid is thinking"
#define WAITING_MSG "Kid is waiting"

#define MAX_THINKING_DELAY 1000
#define MAX_CROSSING_DELAY 70 * (int)1e3
#define STEPS_TO_CROSS 7
#define ROPE_SIZE (STEPS_TO_CROSS + 1)
#define AMOUNT_CROSSED 0 // Index to amount of kids passing

typedef struct kid {
	pid_t pid;
	unsigned int short_id;
	char side;
} Kid;

int find_kid(pid_t kid_pid, Kid *kids, int n_kids);

void apply_random_delay(time_t time);

void kid_think(Kid kid);

void kid_wait(Kid kid);

void kid_cross(Kid kid, pid_t *rope);

void print_rope(pid_t *rope);

void watch_printing_rope(pid_t *rope, int n_crosses);

void fall_kid();

void print_kid_status(Kid kid, char *status);

void fill_kid_info(pid_t kid_pid, Kid *kids, int n_kids, char side);

#endif // PROJECT2_INC_KID_H_

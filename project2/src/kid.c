#include "../inc/kid.h"

int find_kid(pid_t kid_pid, Kid *kids, int n_kids){
	// Could sort and binary search
	int i; for(i = 0; kids[i].pid != kid_pid && i < n_kids; ++i);

	return i;
}

// Time is the maximum value
void apply_random_delay(time_t time) {
    fprintf(stderr, "\n(start) Applying delay of %d miliseconds..\n", (int)time);

    unsigned int seed = clock();
    assert(seed != -1);

    int delay = rand_r(&seed) % time;
    usleep(delay);

    fprintf(stderr, "(success) Delay of %d miliseconds ended\n", (int)time);
}

void print_kid_status(Kid kid, char *status) {
    fprintf(stderr, "%d %s\n", kid.short_id, status);
}

void kid_think(Kid kid) {
    fprintf(stderr, "\n(start) Kid %d starting to think...\n", kid.short_id);

    print_kid_status(kid, THINKING_MSG);
    apply_random_delay(MAX_THINKING_DELAY);

    fprintf(stderr, "(success) Kid %d ended thinking\n", kid.short_id);
}

void swap_side(Kid *kid, int *meta_sh){
	// swap side
	if(kid->side == RIGHT){
		kid->side = LEFT;
		meta_sh[RIGHT_AMOUNT]--;
		meta_sh[LEFT_AMOUNT]++;
	} else {
		kid->side = RIGHT;
		meta_sh[LEFT_AMOUNT]--;
		meta_sh[RIGHT_AMOUNT]++;
	}
}

void kid_cross(Kid kid, pid_t *rope, int *meta_sh) {
    fprintf(stderr, "\n(start) Kid %d starting crossing...\n", kid.short_id);

    int sem_rope = get_ready_semaphores(ROPE_SIZE, 0, 1, ARB_CHAR_A);
    int locking_manage = get_ready_semaphores(LOCKING_MANAGE_SIZE, 0, 1, ARB_CHAR_B);

	// Crosses depending on which side the kid is
	if (kid.side == RIGHT) {
		down(locking_manage, LEFT_LOCK);
		up(locking_manage, LEFT_LOCK);

		meta_sh[CROSSING_AMOUNT]++;
		print_kid_status(kid, CROSSING_MSG);

		for(int i = FIRST_STEP - 1; i <= LAST_STEP; ++i){
			if (i != LAST_STEP) {
				down(sem_rope, i + 1);
				rope[i + 1] = kid.short_id;
				rope[i] = -1;
				up(sem_rope, i);
				usleep(STEP_DELAY);	
			} else {
				rope[i] = -1;
				print_kid_status(kid, CROSSED_MSG);
				up(sem_rope, i);
			}
		}
	} else {
		down(locking_manage, RIGHT_LOCK);
		up(locking_manage, RIGHT_LOCK);

		meta_sh[CROSSING_AMOUNT]++;
		print_kid_status(kid, CROSSING_MSG);

		for(int i = LAST_STEP + 1; i >= FIRST_STEP; --i){
			if (i != FIRST_STEP){
				down(sem_rope, i - 1);
				rope[i - 1] = kid.short_id;
				rope[i] = -1;
				up(sem_rope, i);
				usleep(STEP_DELAY);	
			} else {
				rope[i] = -1;
				print_kid_status(kid, CROSSED_MSG);
				up(sem_rope, i);
			}
		}
	}

	meta_sh[CROSSING_AMOUNT]--;
	meta_sh[CROSSES_TO_END]--;

	swap_side(&kid, meta_sh);

    fprintf(stderr, "(success) Kid %d crossed\n", kid.short_id);
}

void print_rope(pid_t *rope, Kid *kids, int * meta_sh){
	fprintf(stderr, "\n(start) Printing rope...\n");

	for(int i = FIRST_STEP; i <= LAST_STEP; ++i){

		// I has some kid on this rope position
		if(rope[i] != -1){
			const char KID_SIDE = kids[rope[i] - 1].side;

			// Which side are the kid?
			if(KID_SIDE == LEFT && rope[i]){
				fprintf(stdout, "|<-%3d|%s",
						(int) rope[i],
						i != LAST_STEP? "" : "\n");
			} else if (kids[rope[i] - 1].short_id == 0){
				fprintf(stdout, "|bug|%s",
						i != LAST_STEP? "" : "\n");
			}
			else {
				fprintf(stdout, "|%3d->|%s",
						(int) rope[i],
						i != LAST_STEP? "" : "\n");
			}
		} else {
			fprintf(stdout, "%s%s",
					"~~~~~~~",
					i != LAST_STEP? "" : "\n");
		}
	}

    fprintf(stderr, "(success) Rope was printed\n");
}

void watch_printing_rope(pid_t *rope, int n_crosses, Kid *kids, int *meta_sh){
	fprintf(stdout, "\n================================================================\n");

	time_t time_counter = 0;

	while(meta_sh[CROSSES_TO_END] > 0){
		fprintf(stdout, "%10d ms: ", (int)time_counter);
		print_rope(rope, kids, meta_sh);

		usleep(STEP_DELAY);

		time_counter += STEP_DELAY;
	}
	fprintf(stdout, "%10d ms: ", (int)time_counter);
	print_rope(rope, kids, meta_sh);
	fprintf(stdout, "================================================================\n");
}

void fill_kid_info(pid_t kid_pid, Kid *kids, int n_kids, char side) {
   fprintf(stderr, "\nStarting filling information about kid with pid: %d\n", kid_pid);

   int i; for(i = 0; kids[i].pid != -1 && i < n_kids; ++i);
   unsigned int seed = clock();

   kids[i].pid = kid_pid;
   kids[i].short_id = i + 1;
   kids[i].side = side;
   kids[i].crosses = 0;
   kids[i].maximum_crosses = (rand_r(&seed) % MAXIMUM_KIDS_CROSSES) + 2;

   fprintf(stderr, "(success) Filled information about kid with pid: %d\n", kid_pid);
}

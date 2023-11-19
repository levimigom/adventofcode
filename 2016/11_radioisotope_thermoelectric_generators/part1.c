#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../shared/queue.h"
#define TARGET_FLOOR 4
#define MAX_CACHE 17000000

struct arrangement {
	int *chips;
	int *generators;
	int elevator, steps;
};

bool arrangement_is_valid(struct arrangement *arrangement, int units){
	int i, j;

	for(i = 0; i < units; i++){
		// if chip is on an invalid floor
		if(arrangement->chips[i] < 1 || TARGET_FLOOR < arrangement->chips[i]){
			return false;
		}

		// if generator is on an invalid floor
		if(arrangement->generators[i] < 1 || TARGET_FLOOR < arrangement->generators[i]){
			return false;
		}
		
		// if chip is on different floor than its RTG
		if(arrangement->chips[i] != arrangement->generators[i]){
			for(j = 0; j < units; j++){
				// and another RTG is on that floor
				if(i != j && arrangement->chips[i] == arrangement->generators[j]){
					// then the chip is fried
					return false;
				}
			}
		}
	}

	return true;
}

bool all_units_are_on_target_floor(struct arrangement *arrangement, int units){
	int i;

	for(i = 0; i < units; i++){
		if(arrangement->chips[i] != TARGET_FLOOR || arrangement->generators[i] != TARGET_FLOOR){
			return false;
		}
	}

	return true;
}

struct arrangement *create(int *chips, int *generators, int elevator, int steps, int units){
	struct arrangement *arrangement = malloc(sizeof(struct arrangement));
	int i;

	arrangement->chips = calloc(sizeof(int), units);
	arrangement->generators = calloc(sizeof(int), units);

	for(i = 0; i < units; i++){
		arrangement->chips[i] = chips[i];
		arrangement->generators[i] = generators[i];
	}
	
	arrangement->elevator = elevator;
	arrangement->steps = steps;

	return arrangement;
}

struct arrangement *copy(struct arrangement *arrangement, int units){
	return create(arrangement->chips, arrangement->generators, arrangement->elevator, arrangement->steps + 1, units);
}

unsigned int hash(struct arrangement *arrangement, int units){
	unsigned int hash = arrangement->elevator;
	int power = TARGET_FLOOR;
	int i;

	for(i = 0; i < units; i++){
		hash += power * arrangement->chips[i];
		power *= TARGET_FLOOR;
	}

	for(i = 0; i < units; i++){
		hash += power * arrangement->generators[i];
		power *= TARGET_FLOOR;
	}

	return hash;
}

void destroy(struct arrangement* arrangement){
	free(arrangement->chips);
	free(arrangement->generators);
	free(arrangement);
}

void add_arrangement_to_queue(struct arrangement *arrangement, int units, queue *q, bool *cache){
	if(arrangement_is_valid(arrangement, units) && !cache[hash(arrangement, units)]){
		struct arrangement *new_arrangement = copy(arrangement, units);
		enqueue(q, (void*) new_arrangement);
		cache[hash(arrangement, units)] = true;	
	}
}

void try_to_move_one_unit(struct arrangement* arrangement, int units, queue *q, bool *cache){
	int i;

	for(i = 0; i < units; i++){
		if(arrangement->chips[i] == arrangement->elevator){
			// move up
			arrangement->chips[i] = arrangement->elevator = arrangement->elevator + 1;
			add_arrangement_to_queue(arrangement, units, q, cache);
			arrangement->chips[i] = arrangement->elevator = arrangement->elevator - 1;

			// move down
			arrangement->chips[i] = arrangement->elevator = arrangement->elevator - 1;
			add_arrangement_to_queue(arrangement, units, q, cache);
			arrangement->chips[i] = arrangement->elevator = arrangement->elevator + 1;
		}

		if(arrangement->generators[i] == arrangement->elevator){
			// move up
			arrangement->generators[i] = arrangement->elevator = arrangement->elevator + 1;
			add_arrangement_to_queue(arrangement, units, q, cache);
			arrangement->generators[i] = arrangement->elevator = arrangement->elevator - 1;

			// move down
			arrangement->generators[i] = arrangement->elevator = arrangement->elevator - 1;
			add_arrangement_to_queue(arrangement, units, q, cache);
			arrangement->generators[i] = arrangement->elevator = arrangement->elevator + 1;
		}
	}
}

void try_to_move_two_units(struct arrangement* arrangement, int units, queue *q, bool *cache){
	int i, j;

	for(i = 0; i < units; i++){
		if(arrangement->chips[i] == arrangement->elevator){
			for(j = i + 1; j < units; j++){
				if(arrangement->chips[j] == arrangement->elevator){
					// move chip i and j up
					arrangement->chips[i] = arrangement->chips[j] = arrangement->elevator =	arrangement->elevator + 1;
					add_arrangement_to_queue(arrangement, units, q, cache);
					arrangement->chips[i] = arrangement->chips[j] = arrangement->elevator =	arrangement->elevator - 1;

					// move chip i and j down
					arrangement->chips[i] = arrangement->chips[j] = arrangement->elevator =	arrangement->elevator - 1;
					add_arrangement_to_queue(arrangement, units, q, cache);
					arrangement->chips[i] = arrangement->chips[j] = arrangement->elevator =	arrangement->elevator + 1;
				}
			}

			for(j = 0; j < units; j++){
				if(arrangement->generators[j] == arrangement->elevator){
					// move chip i and generator j up
					arrangement->chips[i] = arrangement->generators[j] = arrangement->elevator = arrangement->elevator + 1;
					add_arrangement_to_queue(arrangement, units, q, cache);
					arrangement->chips[i] = arrangement->generators[j] = arrangement->elevator = arrangement->elevator - 1;

					// move chip i and generator j down
					arrangement->chips[i] = arrangement->generators[j] = arrangement->elevator = arrangement->elevator - 1;
					add_arrangement_to_queue(arrangement, units, q, cache);
					arrangement->chips[i] = arrangement->generators[j] = arrangement->elevator = arrangement->elevator + 1;
				}
			}
		}

		if(arrangement->generators[i] == arrangement->elevator){
			for(j = i + 1; j < units; j++){
				if(arrangement->generators[j] == arrangement->elevator){
					// move generator i and generator j up
					arrangement->generators[i] = arrangement->generators[j] = arrangement->elevator = arrangement->elevator + 1;
					add_arrangement_to_queue(arrangement, units, q, cache);
					arrangement->generators[i] = arrangement->generators[j] = arrangement->elevator = arrangement->elevator - 1;
					// move generator i and generator j down
					arrangement->generators[i] = arrangement->generators[j] = arrangement->elevator = arrangement->elevator - 1;
					add_arrangement_to_queue(arrangement, units, q, cache);
					arrangement->generators[i] = arrangement->generators[j] = arrangement->elevator = arrangement->elevator + 1;
				}
			}	
		}
	}
}

void solve(int *chips, int *generators, int elevator, int units){
	bool* cache = calloc(sizeof(bool), MAX_CACHE);
	struct arrangement *arrangement = create(chips, generators, elevator, 0, units);
	queue *q = create_queue();
	int i;

	for(i = 0; i < MAX_CACHE; i++){
		cache[i] = false;
	}

	enqueue(q, (void*) arrangement);
	while(!is_empty(q)){
		arrangement = (struct arrangement*) dequeue(q);
		
		if(all_units_are_on_target_floor(arrangement, units)){
			printf("Arrangement completed after %d steps\n", arrangement->steps);
			break;
		}

		try_to_move_one_unit(arrangement, units, q, cache);
		try_to_move_two_units(arrangement, units, q, cache);
		destroy(arrangement);
	}

	while(!is_empty(q)){
		arrangement = (struct arrangement*) dequeue(q);
		destroy(arrangement);
	}
	
	free(cache);
	free(q);	
}	


int main(){
	// Example testcase
	// 	index 0 = lithium
	// 	index 1 = hydrogen

//	int chips[] = { 1, 1 };
//	int generators[] = { 3, 2 };
//	solve(chips, generators, 1, 2);

	// Real input
	// 	index 0 = strontium
	// 	index 1 = plutonium
	// 	index 2 = thulium
	// 	index 3 = ruthenium 
	// 	index 4 = curium

	int chips[] = { 1, 1, 3, 2, 2 };
	int generators[] = { 1, 1, 2, 2, 2 };
	solve(chips, generators, 1, 5);

	return 0;
}

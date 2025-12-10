/**
 *	author: levimigom
 *	created: 2025-12-10 12:03:35
 **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "button.h"
#include "machine.h"

int my_pow(int x, int e){
	int i, p;

	p = 1;
	for(i = 0; i < e; i++) p *= x;

	return p;
}

int min(int a, int b){ return(a < b ? a : b); }

struct Machine **read_input(int *machine_count){
	struct Machine **machines;
	char s[512];
	int i, machines_size, machines_capacity;

	machines_capacity = 2;
	machines_size = 0;
	machines = calloc(sizeof(struct Machine*), machines_capacity);
	while(scanf("%s", s) != EOF){
		struct Machine *machine = machine_create(s);

		scanf("%s", s);
		while(s[0] == '('){
			struct Button *button = button_create(s);
			machine_add_button(machine, button);
			scanf("%s", s);
		} 
		
		if(machines_capacity == machines_size){
			machines_capacity *= 2;
			machines = realloc(machines, sizeof(struct Machine*) * machines_capacity);
		}

		machines[machines_size++] = machine;
	}

	*machine_count = machines_size;
	return machines;
}

int fewest_button_presses(struct Machine *machine, int button, int lights_bitmask){
	if(lights_bitmask == machine->light_diagram_bitmask){
		return 0;
	}	

	if(button == machine->button_count){
		return machine->button_count + 1;
	}

	// don't use current button
	int dont_use_button = fewest_button_presses(machine, button + 1, lights_bitmask);
	
	// use current button
	int new_bitmask = lights_bitmask;
	int i;

	for(i = 0; i < machine->buttons[button]->light_count; i++){
		new_bitmask ^= my_pow(2, machine->buttons[button]->lights[i]);
	}
	
	int use_button = 1 + fewest_button_presses(machine, button + 1, new_bitmask);

	// return minimum
	return min(dont_use_button, use_button);
}

void solve(){
	// read input
	int i, button_presses, machine_count;
	struct Machine **machines = read_input(&machine_count);

	// calculate solution
	button_presses = 0;
	for(i = 0; i < machine_count; i++) button_presses += fewest_button_presses(machines[i], 0, 0);

	printf("%d\n", button_presses);

	// free memory
	for(i = 0; i < machine_count; i++){
		machine_free(machines[i]);
	}
	free(machines);
}

int main(){
	solve();
	return 0;
}

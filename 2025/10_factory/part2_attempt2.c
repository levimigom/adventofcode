/**
 *	author: levimigom
 *	created: 2025-12-10 12:03:35
 **/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "button.h"
#include "machine.h"

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

		int joltage = 0;
		for(i = 1; s[i] != '\0'; i++){
			if(s[i] == ',' || s[i] == '}'){
				machine_add_joltage(machine, joltage);
				joltage = 0;
			} else {
				joltage = (10 * joltage) + s[i] - '0';
			}
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

int dfs_fewest_button_presses(struct Machine *machine, int button, int *joltage_levels, int total_joltage){
	// dfs because the buttons are sorted in descending order of number of lights affected
	// the first solution we find will be the one with the least button presses
	// 	-> not sure about this, it is likely to be the minimum but not guaranteed i think	

	// solution found -> no more button presses needed
	if(total_joltage == 0){
		return 0;
	}
	
	// all buttons passed -> solution not found
	if(button == machine->button_count){
		return -100000;
	}

	int i, j, solution, max_presses;
	
	// if the remaining joltages are all even, divide by two and recurse
	bool all_even = total_joltage % 2 == 0;
	for(i = 0 ; all_even && i < machine->joltage_level_count; i++){
		all_even = joltage_levels[i] % 2 == 0;
	}

	if(all_even){		
		for(i = 0 ; i < machine->joltage_level_count; i++){
			joltage_levels[i] /= 2;
		}

		return 2 * dfs_fewest_button_presses(machine, button, joltage_levels, total_joltage / 2);
	}


	// find the maximum number of times the current button can be pushed
	max_presses = joltage_levels[machine->buttons[button]->lights[0]];
	for(i = 1; i < machine->buttons[button]->light_count; i++){
		max_presses = min(max_presses, joltage_levels[machine->buttons[button]->lights[i]]);
	}

	// dfs starting from the maximum number of button presses
	total_joltage -= max_presses * machine->buttons[button]->light_count;
	for(i = 0; i < machine->buttons[button]->light_count; i++){
		joltage_levels[machine->buttons[button]->lights[i]] -= max_presses;
	}

	for(i = max_presses; 0 < i; i--){
		// dfs having pressed this button i times
		solution = dfs_fewest_button_presses(machine, button + 1, joltage_levels, total_joltage);
		
		// check if solution has been found
		if(0 <= solution){
			return solution + i;
		}

		// solution not found -> adjust joltage levels for next iteration
		total_joltage += machine->buttons[button]->light_count;
		for(j = 0; j < machine->buttons[button]->light_count; j++){
			joltage_levels[machine->buttons[button]->lights[j]]++;
		}
	}

	// dfs without having pressed the button
	return dfs_fewest_button_presses(machine, button + 1, joltage_levels, total_joltage);
}

int compare( const void* a, const void* b)
{
	struct Button *button_a = *((struct Button**) a);
     	struct Button *button_b = *((struct Button**) b);
     
     	if(button_a->light_count == button_b->light_count) return 0;
     	else if(button_a->light_count < button_b->light_count) return 1;
     	else return -1;
}

int preprocess(struct Machine *machine, int *joltage_levels, int *total_joltage){
	int i, j, k, button_count, button_id, button_presses;

	button_presses = 0;
	for(i = 0; i < machine->joltage_level_count; i++){
		if(joltage_levels[i] == 0){
			continue;
		}
	
		button_count = 0;	
		for(j = 0; j < machine->button_count; j++){
			for(k = 0; k < machine->buttons[j]->light_count; k++){
				if(machine->buttons[j]->lights[k] == i){
					button_count++;
					button_id = j;
				}
			}
		}

		if(1 < button_count) continue;
		
		printf("Joltage %d is only affected by one button (%d)!\n", i, button_id);

		k = joltage_levels[i];
		for(j = 0; j < machine->buttons[button_id]->light_count; j++){
			joltage_levels[machine->buttons[button_id]->lights[j]] -= k;
			*total_joltage -= k;
		}

		button_presses += k;
	}

	return button_presses;
}

void solve(){
	// read input
	int i, j, button_presses, total_button_presses, machine_count;
	struct Machine **machines = read_input(&machine_count);

	// order buttons by count
	for(i = 0; i < machine_count; i++){
		qsort(machines[i]->buttons, machines[i]->button_count, sizeof(struct Button*), compare);
	}

	// calculate solution
	total_button_presses = 0;
	for(i = 0; i < machine_count; i++){
		printf("Machine %d:\n", i);
		//machine_print(machines[i]);

		int *joltage_levels, total_joltage;
		joltage_levels = calloc(sizeof(int), machines[i]->joltage_level_count);
		total_joltage = 0;
		for(j = 0; j < machines[i]->joltage_level_count; j++){
			joltage_levels[j] = machines[i]->joltage_levels[j];
			total_joltage += machines[i]->joltage_levels[j];
		}

		button_presses = preprocess(machines[i], joltage_levels, &total_joltage);
		button_presses += dfs_fewest_button_presses(machines[i], 0, joltage_levels, total_joltage);
		printf("\tButton presses %d: %d\n", i, button_presses);

		total_button_presses += button_presses;
		free(joltage_levels);
	}
	printf("%d\n", total_button_presses);
	
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

struct Machine {
	int light_diagram_length;
	int light_diagram_bitmask;
	int button_count;
	struct Button **buttons;
	int *joltage_levels, joltage_level_count;
};

int parse_light_diagram(char *s){
	int i, bitmask;

	bitmask = 0;
	for(i = strlen(s) - 2; 1 <= i; i--) bitmask = (bitmask << 1) | (s[i] == '#');
	return bitmask;	
}

struct Machine *machine_create(char *light_diagram){
	struct Machine *machine = malloc(sizeof(struct Machine));
	machine->light_diagram_length = strlen(light_diagram) - 2;
	machine->light_diagram_bitmask = parse_light_diagram(light_diagram);
	machine->button_count = 0;
	machine->buttons = 0;
	machine->joltage_levels = 0;
	machine->joltage_level_count = 0;
	return machine;
}

void machine_add_button(struct Machine *machine, struct Button *button){
	if(machine->button_count == 0){
		machine->buttons = malloc(sizeof(struct Button*));
	} else {
		machine->buttons = realloc(machine->buttons, sizeof(struct Button*) * (machine->button_count + 1));
	}

	machine->buttons[machine->button_count++] = button;
}

void machine_add_joltage(struct Machine *machine, int joltage){
	if(machine->joltage_level_count == 0){
		machine->joltage_levels = malloc(sizeof(int));
	} else {
		machine->joltage_levels = realloc(machine->joltage_levels, sizeof(int) * (machine->joltage_level_count + 1));
	}

	machine->joltage_levels[machine->joltage_level_count++] = joltage;
}

void machine_print(struct  Machine *machine){
	printf("Machine:\n");
	printf("\tBitmask: %d (%d bits)\n", machine->light_diagram_bitmask, machine->light_diagram_length);
	
	int i;

	for(i = 0; i < machine->button_count; i++){
		button_print(machine->buttons[i]);
	}

	printf("\tJoltage: ");
	for(i = 0; i < machine->joltage_level_count; i++) printf("%d, ", machine->joltage_levels[i]);
	printf("\n"); 
}

void machine_free(struct Machine *machine){
	int i;

	for(i = 0; i < machine->button_count; i++){
		button_free(machine->buttons[i]);
	}
	free(machine->buttons);

	if(machine->joltage_level_count != 0){
		free(machine->joltage_levels);
	}

	free(machine);
}

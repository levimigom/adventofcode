/**
 *	author: levimigom
 *	created: 2025-08-27 15:27:58
 **/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

enum Gate {
	ASSIGN,
	AND,
	OR,
	NOT,
	LSHIFT,
	RSHIFT
};

struct Command {
	enum Gate gate;
	char lhs[8], rhs[8], out[8];
};

struct Command *create_command(){
	struct Command *c = malloc(sizeof(struct Command));
	c->lhs[0] = c->rhs[0] = c->out[0] = '\0';
	return c;
}

struct Command *read_command(){
	char s[8];

	if(scanf("%s", s) == EOF){
		return 0;
	}
	
	struct Command *c = create_command();

	if(strcmp(s, "NOT") == 0){
		c->gate = NOT;
		scanf("%s %*s %s", c->lhs, c->out);
		return c;
	}
	
	strcpy(c->lhs, s);
	scanf("%s", s);

	if(strcmp(s, "->") == 0){
		c->gate = ASSIGN;
		scanf("%s", c->out);
		return c;
	}

	if(strcmp(s, "AND") == 0){
		c->gate = AND;
	} else if(strcmp(s, "OR") == 0){
		c->gate = OR;
	} else if(strcmp(s, "LSHIFT") == 0){
		c->gate = LSHIFT;
	} else {
		c->gate = RSHIFT;
	}

	scanf("%s %*s %s", c->rhs, c->out);
	return c;
}

struct Wire {
	char id[8];
	bool solved;
	int signal;
	struct Command *command;
};

struct Circuit {
	struct Wire **wires;
	int size, capacity;
};

struct Circuit *create_circuit(){
	struct Circuit *c = malloc(sizeof(struct Circuit));
	c->size = 0;
	c->capacity = 2;
	c->wires = calloc(sizeof(struct Wire*), c->capacity);
	return c;	
}

struct Wire *get_wire(struct Circuit *circuit, char *id){
	int i;

	for(i = 0; i < circuit->size; i++){
		if(strcmp(circuit->wires[i]->id, id) == 0){
			return circuit->wires[i];
		}
	}

	if(circuit->size == circuit->capacity){
		circuit->capacity *= 2;
		circuit->wires = realloc(circuit->wires, sizeof(struct Wire*) * circuit->capacity);
	}
	
	struct Wire *w = malloc(sizeof(struct Wire));
	strcpy(w->id, id);
	w->solved = false;
	circuit->wires[circuit->size++] = w;

	return w;
}

bool is_numeric(char *s){
	while(*s){
		if(*s < '0' || '9' < *s){
			return false;
		}
		s++;
	}
	
	return true;
}

void add_command(struct Circuit *circuit, struct Command *command){
	struct Wire *output_wire = get_wire(circuit, command->out);
	output_wire->command = command;
}

unsigned short evaluate_wire(struct Circuit *circuit, char *id);
unsigned short evaluate_command(struct Circuit *circuit, struct Command *command);

unsigned short evaluate_wire(struct Circuit *circuit, char *id){
	struct Wire *w = get_wire(circuit, id);
	
	if(!w->solved){
		w->solved = true;
		w->signal = evaluate_command(circuit, w->command);
	}

	return w->signal;
}

unsigned short evaluate_command(struct Circuit *circuit, struct Command *command){
	int lhs, rhs;

	if(is_numeric(command->lhs)){
		lhs = atoi(command->lhs);
	} else {
		lhs = evaluate_wire(circuit, command->lhs);
	}

	if(is_numeric(command->rhs)){
		rhs = atoi(command->rhs);
	} else {
		rhs = evaluate_wire(circuit, command->rhs);
	}
	
	switch(command->gate){
		case ASSIGN:
			return lhs;
		case NOT:
			return ~lhs;
		case AND:
			return lhs & rhs;
		case OR:
			return lhs | rhs;
		case LSHIFT:
			return lhs << rhs;
		case RSHIFT:
			return lhs >> rhs;
	}
	
	return 0;
}

void destroy_circuit(struct Circuit *circuit){
	int i;

	for(i = 0; i < circuit->size; i++){
		free(circuit->wires[i]->command);
		free(circuit->wires[i]);
	}
	free(circuit->wires);
	free(circuit);
}

int main(){
	struct Command *command;
	struct Circuit *circuit = create_circuit();	

	while(command = read_command()){
		add_command(circuit, command);
	}

	printf("%d\n", evaluate_wire(circuit, "a"));

	destroy_circuit(circuit);

	return 0;
}

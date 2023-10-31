#include <stdio.h>
#include <stdlib.h>
#define MAX_INSTRUCTION_LENGTH 32
#define bool char
#define true 1
#define false 0

int get_number_of_steps_from_instruction(char* instruction){
	int steps = 0;

	while(*instruction){
		if('0' <= *instruction && *instruction <= '9'){
			steps = (steps * 10) + (*instruction - '0');
		}
		instruction++;
	}

	return steps;
}

void change_direction(int* direction, char turn){
	if(turn == 'L'){
		(*direction)--;	
	} else {
		(*direction)++;
	}

	*direction = (*direction + 4) % 4;
}

void move_in_direction(int* x, int* y, int direction){
	// 0 = North
	if(direction == 0){
		(*y)--;
	}

	// 1 = East
	else if(direction == 1){
		(*x)++;
	}

	// 2 = South
	else if(direction == 2){
		(*y)++;
	}

	// 3 = West
	else {
		(*x)--;
	}
}

struct list {
	int** list;
	int length, size;
};

struct list* init_visited(){
	struct list *visited = malloc(sizeof(struct list));

	visited->size = 32;
	visited->length = 0;
	visited->list = calloc(sizeof(int *), visited->size);
	
	return visited;
}

bool is_visited(int x, int y, struct list* visited){
	int i;

	for(i = 0; i < visited->length; i++){
		if(visited->list[i][0] == x && visited->list[i][1] == y){
			return true;
		}
	}

	return false;
}

void add_visited(int x, int y, struct list* visited){
	if(visited->length == visited->size){
		visited->size *= 2;
		visited->list = realloc(visited->list, visited->size * sizeof(int*)); 
	}

	visited->list[visited->length] = calloc(sizeof(int), 2);
	visited->list[visited->length][0] = x;
	visited->list[visited->length][1] = y;
	visited->length++;
}

void destroy_visited(struct list *visited){
	int i;

	for(i = 0; i < visited->length; i++){
		free(visited->list[i]);
	}

	free(visited->list);
	free(visited);
}

int abs(int n){
	if(n < 0){
		return -n;
	} else {
		return n;
	}
}

int main(){
	int x, y, direction, steps;
	char turn, instruction[MAX_INSTRUCTION_LENGTH];
	bool loop_found;
	struct list* visited = init_visited();

	x = y = direction = 0;
	loop_found = false;
	while(!loop_found && scanf("%s", instruction) != EOF){
		turn = instruction[0];
		steps = get_number_of_steps_from_instruction(instruction);

		change_direction(&direction, turn);

		while(!loop_found && steps--){
			move_in_direction(&x, &y, direction);

			if(is_visited(x, y, visited)){
				printf("%d %d has already been visited (distance from start = %d blocks)\n", x, y, abs(x) + abs(y));
				loop_found = true;
			} else {
				add_visited(x, y, visited);
			}
		}
	}

	destroy_visited(visited);

	return 0;
}

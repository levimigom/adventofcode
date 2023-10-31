#include <stdio.h>
#define MAX_INSTRUCTION_LENGTH 32

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

void move_in_direction(int* x, int* y, int direction, int steps){
	// 0 = North
	if(direction == 0){
		*y -= steps;
	}

	// 1 = East
	else if(direction == 1){
		*x += steps;
	}

	// 2 = South
	else if(direction == 2){
		*y += steps;
	}

	// 3 = West
	else {
		*x -= steps;
	}
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

	x = y = 0;
	while(scanf("%s", instruction) != EOF){
		turn = instruction[0];
		steps = get_number_of_steps_from_instruction(instruction);

		change_direction(&direction, turn);
		move_in_direction(&x, &y, direction, steps);
	}

	printf("final location = %d %d (distance from start = %d blocks)\n", x, y, abs(x) + abs(y));

	return 0;
}

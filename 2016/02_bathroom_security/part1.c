#include <stdio.h>
#define ROWS 3
#define COLS 3

// 1 2 3
// 4 5 6
// 7 8 9
int get_digit(int row, int col){
	return row * 3 + col + 1;
}

void follow_instruction(int* row, int *col, char instruction){	
	if(instruction == 'U'){
		*row = *row - 1;
	} else if(instruction == 'D'){
		*row = *row + 1;	
	} else if(instruction == 'L'){
		*col = *col - 1;
	} else {
		*col = *col + 1;
	}
}

void ensure_position_is_on_keypad(int* row, int *col){
	if(*row < 0){
		*row = 0;
	}	

	if(*row == ROWS){
		*row = ROWS - 1;
	}

	if(*col < 0){
		*col = 0;
	}

	if(*col == COLS){
		*col = COLS - 1;
	}
}

int main(){
	int row, col, code;
	char instruction;

	code = 0;
	row = col = 1;
	while(scanf("%c", &instruction) != EOF){
		if(instruction == '\n'){	
			code = (code * 10) + get_digit(row, col);
		} else {
			follow_instruction(&row, &col, instruction);
		}

		ensure_position_is_on_keypad(&row, &col);	
	}

	printf("%d\n", code);

	return 0;
}

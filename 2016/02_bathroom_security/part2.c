#include <stdio.h>
#define ROWS 5
#define COLS 5
#define bool unsigned char
#define false 0

//     1
//   2 3 4
// 5 6 7 8 9
//   A B C
//     D
char keypad[ROWS][COLS] = {
	{ 0  , 0  , '1', 0  , 0   },
       	{ 0  , '2', '3', '4', 0   },
       	{ '5', '6', '7', '8', '9' },
       	{ 0  , 'A', 'B', 'C', 0   },
       	{ 0  , 0  , 'D', 0  , 0   }
};

bool position_is_valid(int row, int col){
	if(row < 0 || row == ROWS){
		return false;	
	}

	if(col < 0 || col == COLS){
		return false;
	}

	return keypad[row][col] != 0;
}

void follow_instruction(int *row, int *col, char instruction){
	int new_row = *row;
	int new_col = *col;

	if(instruction == 'U'){
		new_row--;
	} else if(instruction == 'D'){
		new_row++;
	} else if(instruction == 'L'){
		new_col--;
	} else {
		new_col++;
	}

	if(position_is_valid(new_row, new_col)){
		*row = new_row;
		*col = new_col;
	}
}

int main(){ 
	int row, col;
	char instruction;

	row = 2;
	col = 0;

	while(scanf("%c", &instruction) != EOF){
		if(instruction == '\n'){
			printf("%c", keypad[row][col]);
		} else {
			follow_instruction(&row, &col, instruction);
		}
	}

	printf("\n");

	return 0;
}


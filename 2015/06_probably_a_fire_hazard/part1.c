/**
 *	author: levimigom
 *	created: 2025-08-27 14:42:15
 **/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define ROWS 1000
#define COLS 1000

enum Instruction {
	TOGGLE,
	TURN_ON,
	TURN_OFF
};

struct Command {
	enum Instruction instruction;
	int from_x, from_y, to_x, to_y;
};

struct Command *read_command(){
	char s[16];
	
	if(scanf("%s", s) == EOF){
		return 0;
	}

	struct Command *c = malloc(sizeof(struct Command));

	if(strcmp(s, "toggle") == 0){
		c->instruction = TOGGLE;
	} else {
		scanf("%s", s);
		
		if(strcmp(s, "off") == 0){
			c->instruction = TURN_OFF;
		} else {
			c->instruction = TURN_ON;
		}
	}

	scanf("%d,%d %*s %d,%d", &(c->from_x), &(c->from_y), &(c->to_x), &(c->to_y));

	return c;
}

void execute_command(bool **grid, int rows, int cols, struct Command *c){
	int i, j;

	for(i = c->from_x; i < rows && i <= c->to_x; i++){
		for(j = c->from_y; j < cols && j <= c->to_y; j++){
			switch(c->instruction){
				case TOGGLE:
					grid[i][j] = !grid[i][j];
					break;
				case TURN_ON:
					grid[i][j] = true;
					break;
				case TURN_OFF:
					grid[i][j] = false;
					break;
			}
		}
	}
}

bool **create_grid(int rows, int cols){
	bool **grid = calloc(sizeof(bool*), rows);
	int i, j;

	for(i = 0; i < rows; i++){
		grid[i] = calloc(sizeof(bool), cols);
		for(j = 0; j < cols; j++){
			grid[i][j] = false;
		}
	}

	return grid;
}

int count_lit_lights(bool **grid, int rows, int cols){
	int i, j, count;

	for(i = count = 0; i < rows; i++){
		for(j = 0; j < cols; j++){
			if(grid[i][j]){
				count++;
			}
		}
	}
	
	return count;
}

void free_grid(bool **grid, int rows){
	int i;

	for(i = 0; i < rows; i++){
		free(grid[i]);
	}
	free(grid);
}

int main(){
	struct Command *c;
	bool **grid = create_grid(ROWS, COLS);

	while(c = read_command()){
		execute_command(grid, ROWS, COLS, c); 
		free(c);
	}

	printf("%d\n", count_lit_lights(grid, ROWS, COLS));
	free_grid(grid, ROWS);

	return 0;
}

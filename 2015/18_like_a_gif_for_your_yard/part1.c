/**
 *	author: levimigom
 *	created: 2025-09-23 18:00:08
 **/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define ROWS 100
#define COLS 100
#define STEPS 100
#define NEIGHBOURS 8
int xp[] = { 0, 0, 1, 1, 1, -1, -1, -1 };
int yp[] = { 1, -1, 0, 1, -1, 0, 1, -1 };

int count_on_lights(bool **lights){
	int i, j, on_lights;

	on_lights = 0;
	for(i = 0; i < ROWS; i++){
		for(j = 0; j < COLS; j++){
			if(lights[i][j]){
				on_lights++;
			}
		}
	}
	
	return on_lights;
}

void copy(bool **src, bool **dst){
	int i, j;

	for(i = 0; i < ROWS; i++){
		for(j = 0; j < COLS; j++){
			dst[i][j] = src[i][j];
		}
	}
}

bool is_within_bounds(int row, int col){
	return(0 <= row && row < ROWS && 0 <= col && col < COLS);
}

int count_on_neighbours(bool **state, int row, int col){
	int i, on_neighbours, neighbour_row, neighbour_col;

	on_neighbours = 0;
	for(i = 0; i < NEIGHBOURS; i++){
		neighbour_row = row + xp[i];
		neighbour_col = col + yp[i];

		if(is_within_bounds(neighbour_row, neighbour_col) && state[neighbour_row][neighbour_col]){
			on_neighbours++;
		}
	}

	return on_neighbours;
}

void update(bool **lights, bool **state){
	int i, j, on_neighbours;

	for(i = 0; i < ROWS; i++){
		for(j = 0; j < COLS; j++){
			on_neighbours = count_on_neighbours(state, i, j);
		
			if(state[i][j] && (on_neighbours != 2 && on_neighbours != 3)){
				lights[i][j] = false;
			}

			if(!state[i][j] && on_neighbours == 3){
				lights[i][j] = true;
			}
		}
	}	
}

void print_lights(bool **lights){
	int i, j;

	for(i = 0; i < COLS; i++){
		printf("-");
	}
	printf("\n");

	for(i = 0; i < ROWS; i++){
		for(j = 0; j < COLS; j++){
			printf("%c", lights[i][j] ? '#' : '.');
		}
		printf("\n");
	}
}

void transform(bool **lights){
	int i;
	bool **state = calloc(sizeof(int*), ROWS);

	for(i = 0; i < ROWS; i++){
		state[i] = calloc(sizeof(int), COLS);
	}

	for(i = 0; i < STEPS; i++){
		copy(lights, state);
		update(lights, state);
	}

	for(i = 0; i < ROWS; i++){
		free(state[i]);
	}
	free(state);
}

bool **read_input(){
	int i, j;
	bool **lights = calloc(sizeof(bool*), ROWS);

	for(i = 0; i < ROWS; i++){
		lights[i] = calloc(sizeof(bool), COLS);
		for(j = 0; j < COLS; j++){
			lights[i][j] = getchar() == '#';
		}
		getchar();
	}

	return lights;
}

int main(){
	bool **lights = read_input();
	
	transform(lights);

	printf("%d\n", count_on_lights(lights));

	int i;

	for(i = 0; i < ROWS; i++){
		free(lights[i]);
	}
	free(lights);

	return 0;
}

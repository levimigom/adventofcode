/**
 *	author: levimigom
 *	created: 2025-12-04 20:36:48
 **/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIRECTIONS 8
#define DIM 256
#define ROLL_OF_PAPER '@'
int xp[] = { 0, 0, 1, 1, 1, -1, -1, -1 };
int yp[] = { 1, -1, 0, 1, -1, 0, 1, -1 };

bool is_within_bounds(int row, int col, int rows, int cols){
	return(0 <= row && row < rows && 0 <= col && col < cols);
}

int count_neighbours(char grid[DIM][DIM], int row, int col, int rows, int cols){
	int i, count, neighbour_row, neighbour_col;

	for(i = count = 0; i < DIRECTIONS; i++){
		neighbour_row = row + xp[i];
		neighbour_col = col + yp[i];

		if(is_within_bounds(neighbour_row, neighbour_col, rows, cols)
			&& grid[neighbour_row][neighbour_col] == ROLL_OF_PAPER){
			count++;
		}
	}

	return count;
}

void read_grid(char grid[DIM][DIM], int *rows, int *cols){
	int i;

	for(i = 0; scanf("%s", grid[i]) != EOF; i++);

	*rows = i;
	*cols = strlen(grid[0]);
}

void solve(){
	char grid[DIM][DIM];
	int i, j, rows, cols, count;

	read_grid(grid, &rows, &cols);
	
	for(i = count = 0; i < rows; i++){
		for(j = 0; j < cols; j++){
			if(grid[i][j] == ROLL_OF_PAPER && count_neighbours(grid, i, j, rows, cols) < 4){
				count++;		
			}	
		}
	}

	printf("%d\n", count);
}

int main(){
	solve();
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "string.h"

char **read_grid(int *rows, int *cols){
	int row, row_capacity;
	String *s;

	row_capacity = 1;
	char **grid = calloc(sizeof(char*), row_capacity);

	row = 0;
	while(s = string_read_line()){
		*cols = s->length;

		if(row == row_capacity){
			row_capacity *= 2;
			grid = realloc(grid, sizeof(char*) * row_capacity);
		}

		grid[row++] = string_get_characters(s);
		string_free(s);
	}

	*rows = row;

	return grid;
}

bool is_within_bounds(int rows, int cols, int row, int col){
	return(0 <= row && row < rows && 0 <= col && col < cols);
}

void mark_antinode(int rows, int cols, bool **is_antinode, int row, int col){
	if(is_within_bounds(rows, cols, row, col)){
		is_antinode[row][col] = true;
	}
}

void mark_antinodes(char **grid, int rows, int cols, bool **is_antinode, int row, int col){
	int i, j, row_diff, col_diff;
	
	for(i = 0; i <= row; i++){
		for(j = 0; j < cols && (i < row || j < col); j++){
			if(grid[row][col] == grid[i][j]){
				row_diff = row - i;
				col_diff = col - j;

				mark_antinode(rows, cols, is_antinode, i - row_diff, j - col_diff);
				mark_antinode(rows, cols, is_antinode, row + row_diff, col + col_diff);
			}
		}
	}
}

void solve(char **grid, int rows, int cols){
	int i, j;
	bool **is_antinode = calloc(sizeof(bool*), rows);	

	for(i = 0; i < rows; i++){
		is_antinode[i] = calloc(sizeof(bool), cols);

		for(j = 0; j < cols; j++){
			is_antinode[i][j] = false;
		}
	}

	for(i = 0; i < rows; i++){
		for(j = 0; j < cols; j++){
			if(grid[i][j] != '.'){
				mark_antinodes(grid, rows, cols, is_antinode, i, j);
			}
		}
	}

	int antinodes = 0;

	for(i = 0; i < rows; i++){
		for(j = 0; j < cols; j++){
			if(is_antinode[i][j]){
				antinodes++;
			}
		}
		free(is_antinode[i]);
	}
	free(is_antinode);

	printf("%d\n", antinodes);
}

int main(){
	int i, j, rows, cols;
	char **grid = read_grid(&rows, &cols);

	solve(grid, rows, cols);

	for(i = 0; i < rows; i++){
		free(grid[i]);
	}
	free(grid);

	return 0;
}

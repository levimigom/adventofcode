#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "helper.h"
#define DIRECTIONS 4
int row_directions[] = { 1, -1, 0, 0 };
int col_directions[] = { 0, 0, 1, -1 };

bool **create_visited_arr(int rows, int cols){
	int i, j;
	bool **visited = calloc(sizeof(bool *), rows);

	for(i = 0; i < rows; i++){
		visited[i] = calloc(sizeof(bool), cols);

		for(j = 0; j < cols; j++){
			visited[i][j] = false;
		}	
	}

	return visited;
}

bool is_within_bounds(int rows, int cols, int row, int col){
	return(0 <= row && row < rows && 0 <= col && col < cols);
}

void dfs_region(char **garden, int rows, int cols, int row, int col, bool **visited, int *area, int *perimeter){
	int i, neighbour_row, neighbour_col;

	visited[row][col] = true;
	*area += 1;

	for(i = 0; i < DIRECTIONS; i++){
		neighbour_row = row + row_directions[i];
		neighbour_col = col + col_directions[i];

		if(is_within_bounds(rows, cols, neighbour_row, neighbour_col)){
			if(garden[row][col] == garden[neighbour_row][neighbour_col] && !visited[neighbour_row][neighbour_col]){
				dfs_region(garden, rows, cols, neighbour_row, neighbour_col, visited, area, perimeter);
			}

			if(garden[row][col] != garden[neighbour_row][neighbour_col]){
				*perimeter += 1;
			}	
		} else {
			*perimeter += 1;
		}
	}
}

void solve(char **garden, int rows, int cols){
	int i, j, area, perimeter, total_price;
	bool **visited = create_visited_arr(rows, cols);
	
	total_price = 0;
	for(i = 0; i < rows; i++){
		for(j = 0; j < cols; j++){
			if(!visited[i][j]){
				area = perimeter = 0;

				dfs_region(garden, rows, cols, i, j, visited, &area, &perimeter);
				total_price += area * perimeter;
			}
		}
	}

	printf("%d\n", total_price);

	free_2d_arr((void**) visited, rows);
}

int main(){
	int rows, cols;
	char **garden = read_grid(&rows, &cols);

	solve(garden, rows, cols);	

	free_2d_arr((void **) garden, rows);

	return 0;
}

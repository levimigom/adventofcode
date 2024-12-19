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

bool ***create_perimeter_arr(int rows, int cols){
	bool ***perimeter = calloc(sizeof(bool**), DIRECTIONS);
	int i;

	for(i = 0; i < DIRECTIONS; i++){
		perimeter[i] = create_visited_arr(rows, cols);
	}

	return perimeter;
}

void free_perimeter_arr(bool ***perimeter, int rows){
	int i;

	for(i = 0; i < DIRECTIONS; i++){
		free_2d_arr((void **) perimeter[i], rows);
	}
	free(perimeter);
}

bool is_within_bounds(int rows, int cols, int row, int col){
	return(0 <= row && row < rows && 0 <= col && col < cols);
}

void dfs_region(char **garden, int rows, int cols, int row, int col, bool **visited, int *area, bool ***perimeter){
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
				perimeter[i][row][col] = true;
			}	
		} else {
			perimeter[i][row][col] = true;
		}
	}
}

int count_sides(int rows, int cols, bool **perimeter, int direction){
	int row, col, neighbour_row, neighbour_col, sides;
	bool **visited = create_visited_arr(rows, cols);

	sides = 0;
	for(row = 0; row < rows; row++){
		for(col = 0; col < cols; col++){
			if(perimeter[row][col] && !visited[row][col]){
				sides++;

				visited[row][col] = true;

				neighbour_row = row + row_directions[direction];
				neighbour_col = col + col_directions[direction];

				while(is_within_bounds(rows, cols, neighbour_row, neighbour_col) 
						&& perimeter[neighbour_row][neighbour_col]){
					visited[neighbour_row][neighbour_col] = true;

					neighbour_row += row_directions[direction];
					neighbour_col += col_directions[direction];
				}
			}	
		}
	}

	free_2d_arr((void**) visited, rows);

	return sides;
}

void solve(char **garden, int rows, int cols){
	int i, j, area, sides, total_price;
	bool **visited = create_visited_arr(rows, cols);
	
	total_price = 0;
	for(i = 0; i < rows; i++){
		for(j = 0; j < cols; j++){
			if(!visited[i][j]){
				bool ***perimeter = create_perimeter_arr(rows, cols);
				area = 0;

				dfs_region(garden, rows, cols, i, j, visited, &area, perimeter);

				sides = 0;
				
				// down
				sides += count_sides(rows, cols, perimeter[0], 2);
				// up
				sides += count_sides(rows, cols, perimeter[1], 2);
				// right
				sides += count_sides(rows, cols, perimeter[2], 0);
				// left
				sides += count_sides(rows, cols, perimeter[3], 0);
				
				total_price += area * sides;

				free_perimeter_arr(perimeter, rows);
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

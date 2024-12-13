#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "string.h"
#define DIRECTIONS 4
int row_directions[] = { 1, -1, 0, 0 };
int col_directions[] = { 0, 0, 1, -1 };

char **read_map(int *rows, int *cols){
	int i, capacity;
	String *s;
	
	capacity = 1;
	*rows = *cols = 0;

	char **map = calloc(sizeof(char*), capacity);
	while(s = string_read_line()){
		if(*rows == capacity){
			capacity *= 2;
			map = realloc(map, sizeof(char*) * capacity);
		}

		map[(*rows)++] = string_get_characters(s);
		*cols = string_length(s);	
	       	string_free(s);
	}

	return map;
}

void free_2d_arr(void **map, int rows){
	int i;
	
	for(i = 0; i < rows; i++){
		free(map[i]);
	}

	free(map);
}

bool **create_visited_cache(int rows, int cols){
	int i;
	bool **visited = calloc(sizeof(bool*), rows);

	for(i = 0; i < rows; i++){
		visited[i] = calloc(sizeof(bool), cols);
	}

	return visited;
}

void reset_visited_cache(bool **visited, int rows, int cols){
	int i, j;

	for(i = 0; i < rows; i++){
		for(j = 0; j < cols; j++){
			visited[i][j] = false;
		}
	}
}

bool is_within_bounds(int rows, int cols, int row, int col){
	return(0 <= row && row < rows && 0 <= col && col < cols);
}

int get_score(char **map, bool **visited, int rows, int cols, int row, int col){
	visited[row][col] = true;

	if(map[row][col] == '9'){
		return 1;
	}

	int i, score, neighbour_row, neighbour_col;

	for(i = score = 0; i < DIRECTIONS; i++){
		neighbour_row = row + row_directions[i];
		neighbour_col = col + col_directions[i];

		if(is_within_bounds(rows, cols, neighbour_row, neighbour_col) 
				&& map[neighbour_row][neighbour_col] == map[row][col] + 1
					&& !visited[neighbour_row][neighbour_col]){
			score += get_score(map, visited, rows, cols, neighbour_row, neighbour_col);
		}
	}

	return score;
}

int get_total_score(char **map, int rows, int cols){
	int i, j, score;
	bool **visited = create_visited_cache(rows, cols);
	
	for(i = score = 0; i < rows; i++){
		for(j = 0; j < cols; j++){
			if(map[i][j] == '0'){
				reset_visited_cache(visited, rows, cols);
				score += get_score(map, visited, rows, cols, i, j);
			}
		}
	}

	free_2d_arr((void **) visited, rows);
	return score;
}

int main(){
	int i, j, rows, cols;
	char **map = read_map(&rows, &cols);
	
	printf("%d\n", get_total_score(map, rows, cols));
	
	free_2d_arr((void **) map, rows);

	return 0;
}

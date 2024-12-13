#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "string.h"
#define OBSTACLE '#'
#define EMPTY '.'
#define DIRECTIONS 4
int row_directions[] = { -1, 0, 1, 0 }; // up, right, down, left
int col_directions[] = { 0, 1, 0, -1 }; // up, right, down, left

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

void free_2d_arr(void **arr, int rows){
        int i;

        for(i = 0; i < rows; i++){
                free(arr[i]);
        }

        free(arr);
}

bool is_within_bounds(int rows, int cols, int row, int col){
	return(0 <= row && row < rows && 0 <= col && col < cols);
}

int get_direction(char c){
	char directions[] = { '^', '>', 'v', '<' };
	int i;
	
	for(i = 0; i < DIRECTIONS; i++){
		if(directions[i] == c){
			return i;
		}
	}

	return 0;
}

int get_next_direction(int direction){
	return((direction + 1) % DIRECTIONS);
}

bool contains_loop(char **map, bool ***visited, int rows, int cols, int row, int col, int direction){
	int next_row, next_col;

	while(is_within_bounds(rows, cols, row, col)){
		if(visited[row][col][direction]){
			return true;
		}

		visited[row][col][direction] = true;
		next_row = row + row_directions[direction];
		next_col = col + col_directions[direction];

		if(is_within_bounds(rows, cols, next_row, next_col) && map[next_row][next_col] == OBSTACLE){
			direction = get_next_direction(direction);
		} else {
			row = next_row;
			col = next_col;
		}	
	}

	return false;
}

bool ***create_visited_cache(int rows, int cols){
        int i, j;
        bool ***visited = calloc(sizeof(bool**), rows);

        for(i = 0; i < rows; i++){
                visited[i] = calloc(sizeof(bool*), cols);
		for(j = 0; j < cols; j++){
			visited[i][j] = calloc(sizeof(bool), DIRECTIONS);
		}
        }

        return visited;
}

void reset_visited_cache(bool ***visited, int rows, int cols){
        int i, j, k;

        for(i = 0; i < rows; i++){
                for(j = 0; j < cols; j++){
                        for(k = 0; k < DIRECTIONS; k++){
				visited[i][j][k] = false;
			}
                }
        }
}

void free_visited_cache(bool ***visited, int rows, int cols){
	int i, j;

	for(i = 0; i < rows; i++){
		for(j = 0; j < cols; j++){
			free(visited[i][j]);
		}
		free(visited[i]);
	}
	free(visited);
}

int count_loops(char **map, int rows, int cols, int guard_row, int guard_col, int direction){
	int i, j, loops;
	bool ***visited = create_visited_cache(rows, cols);

	for(i = loops = 0; i < rows; i++){
		for(j = 0; j < cols; j++){
			if(map[i][j] == EMPTY){
				map[i][j] = OBSTACLE;
				
				reset_visited_cache(visited, rows, cols);
				if(contains_loop(map, visited, rows, cols, guard_row, guard_col, direction)){
					loops++;
				}
		
				map[i][j] = EMPTY;
			}		
		}
	}

	free_visited_cache(visited, rows, cols);

	return loops;
}

void find_guard_position(char **map, int rows, int cols, int *row, int *col){
	int i, j;

	for(i = 0; i < rows; i++){
		for(j = 0; j < cols; j++){
			if(map[i][j] != EMPTY && map[i][j] != OBSTACLE){
				*row = i;
				*col = j;
				return;
			}
		}
	}
}

int main(){
	int rows, cols, guard_row, guard_col;
	char **map = read_map(&rows, &cols);
	
	find_guard_position(map, rows, cols, &guard_row, &guard_col);
	printf("%d\n", count_loops(map, rows, cols, guard_row, guard_col, get_direction(map[guard_row][guard_col])));
	free_2d_arr((void **) map, rows);

	return 0;
}

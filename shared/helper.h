#include <stdlib.h>
#include "string.h"

#ifndef HELPER_H
#define HELPER_H

char **read_grid(int *rows, int *cols){
	int i, capacity;
        String *s;

        capacity = 1;
        *rows = *cols = 0;

        char **grid = calloc(sizeof(char*), capacity);
        while(s = string_read_line()){
                if(*rows == capacity){
                        capacity *= 2;
                        grid = realloc(grid, sizeof(char*) * capacity);
                }

                grid[(*rows)++] = string_get_characters(s);
                *cols = string_length(s);
                string_free(s);
        }

        return grid;
}

void free_2d_arr(void **map, int rows){
        int i;

        for(i = 0; i < rows; i++){
                free(map[i]);
        }

        free(map);
}

#endif

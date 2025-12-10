/**
 *	author: levimigom
 *	created: 2025-12-09 16:35:44
 **/
#include <stdio.h>
#include <stdlib.h>
#define LIM 512

int **read_input(int *rows){
	char s[64];
	int **tiles, size, capacity, i, state;

	capacity = 2;
	tiles = calloc(sizeof(int*), capacity);

	for(size = 0; scanf("%s", s) != EOF; size++){
		if(size == capacity){
			capacity *= 2;
			tiles = realloc(tiles, sizeof(int*) * capacity);
		}

		tiles[size] = calloc(sizeof(int), 2);
		tiles[size][0] = tiles[size][1] = 0;		

		state = 0;
		for(i = 0; s[i] != '\0'; i++){
			if(s[i] == ','){
				state = 1;
			} else {
				tiles[size][state] = (10 * tiles[size][state]) + s[i] - '0';
			}
		}
	}

	*rows = size;
	return tiles;
}

long my_abs(long n){ return(n < 0 ? -n : n); }
long max(long a, long b){ return(a < b ? b : a); }

long rectangle_size(long x1, long y1, long x2, long y2){
	return (1 + my_abs(x1 - x2)) * (1 + my_abs(y1 - y2));
}

long calculate_largest_rectangle(int **tiles, int tile_count){
	int i, j;
	long max_size;

	max_size = 0;
	for(i = 0; i < tile_count; i++){
		for(j = i + 1; j < tile_count; j++){
			max_size = max(max_size, rectangle_size(tiles[i][0], tiles[i][1], tiles[j][0], tiles[j][1]));
		}
	}

	return max_size;
}

void solve(){
	int i, tile_count;
	int **tiles = read_input(&tile_count);

	printf("%ld\n", calculate_largest_rectangle(tiles, tile_count));

	// free allocated memory
	for(i = 0; i < tile_count; i++){
		free(tiles[i]);
	}
	free(tiles);
}

int main(){
	solve();
	return 0;
}

/**
 *	author: levimigom
 *	created: 2025-12-17 10:06:47
 **/
#include <stdio.h>
#include <stdlib.h>
#define PRESENTS 6
#define ROWS 3
#define COLS 3

struct Present {
	int tiles;
	char shape[ROWS][COLS + 1];
};

struct Present **read_presents(){
	struct Present **presents = calloc(sizeof(struct Present*), PRESENTS);
	int i, j, k;

	for(i = 0; i < PRESENTS; i++){
		presents[i] = malloc(sizeof(struct Present));
		presents[i]->tiles = 0;
		
		for(j = 0; j < ROWS; j++){
			scanf("%s", presents[i]->shape[j]);

			for(k = 0; k < COLS; k++){
				presents[i]->tiles += presents[i]->shape[j][k] == '#';
			}
		}
	}

	return presents;
}

void solve(struct Present **presents){
	int i, rows, cols, total_tiles, n, solution;

	solution = 0;
	while(scanf("%dx%d:", &rows, &cols) != EOF){
		total_tiles = 0;

		for(i = 0; i < PRESENTS; i++){
			scanf("%d", &n);
			total_tiles += n * presents[i]->tiles;
		}

		if(total_tiles <= rows * cols) solution++;
	}

	printf("%d\n", solution);
}

int main(){
	struct Present **presents = read_presents();
	int i;

	solve(presents);	

	for(i = 0; i < PRESENTS; i++) free(presents[i]);
	free(presents);

	return 0;
}

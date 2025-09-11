/**
 *	author: levimigom
 *	created: 2025-09-11 21:08:39
 **/
#include <stdio.h>
#include <stdlib.h>
#define SECONDS 2503
#define LIM 16

struct Reindeer {
	int speed, fly, rest, distance, score;
};

struct Reindeer **read_input(int *size){
	int i, speed, fly, rest;
	struct Reindeer **reindeer = calloc(sizeof(struct Reindeer*), LIM);

	for(i = 0; scanf("%*s can fly %d km/s for %d seconds, but then must rest for %d seconds.", &speed, &fly, &rest) != EOF; i++){
		reindeer[i] = malloc(sizeof(struct Reindeer));
		reindeer[i]->speed = speed;
		reindeer[i]->fly = fly;
		reindeer[i]->rest = rest;
		reindeer[i]->distance = reindeer[i]->score = 0;
	}

	*size = i;
	return reindeer;
}

int max(int a, int b){ return(a < b ? b : a); }

void calculate_maximum_score(struct Reindeer **reindeer, int size){
	int i, j, maximum_distance, maximum_score;

	maximum_distance = 0;
	for(i = 0; i < SECONDS; i++){
		// adjust distances
		for(j = 0; j < size; j++){
			if((i % (reindeer[j]->fly + reindeer[j]->rest)) < reindeer[j]->fly){
				reindeer[j]->distance += reindeer[j]->speed;
				maximum_distance = max(maximum_distance, reindeer[j]->distance);
			}
		}
		
		// add score to leading reindeer
		for(j = 0; j < size; j++){
			if(reindeer[j]->distance == maximum_distance){
				reindeer[j]->score++;
			}
		}
	}

	maximum_score = 0;
	for(i = 0; i < size; i++){
		maximum_score = max(maximum_score, reindeer[i]->score);
	}

	printf("%d\n", maximum_score);
}

int main(){
	int i, size;
	struct Reindeer **reindeer = read_input(&size);

	calculate_maximum_score(reindeer, size);

	for(i = 0; i < size; i++){
		free(reindeer[i]);
	}
	free(reindeer);
	
	return 0;
}

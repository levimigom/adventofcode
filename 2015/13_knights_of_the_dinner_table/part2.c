/**
 *	author: levimigom
 *	created: 2025-09-10 17:11:55
 **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#define STRING_LEN 32
#define MAX_SIZE 12

struct Configuration {
	int size, capacity, **happiness;
	char **names;
};

struct Configuration *configuration_create(int people){
	struct Configuration *config = malloc(sizeof(struct Configuration));
	config->size = 0;
	config->capacity = people;
	config->names = calloc(sizeof(char*), people);
	config->happiness = calloc(sizeof(int*), people);

	int i;

	for(i = 0; i < people; i++){
		config->happiness[i] = calloc(sizeof(int), people);
	}

	return config;
}

void configuration_free(struct Configuration *config){
	int i;

	for(i = 0; i < config->size; i++){
		free(config->names[i]);
	}

	for(i = 0; i < config->capacity; i++){
		free(config->happiness[i]);
	}

	free(config->names);
	free(config->happiness);
	free(config);
}

int configuration_get_person_index(struct Configuration *config, char *name){
	int i;

	for(i = 0; i < config->size; i++){
		if(strcmp(name, config->names[i]) == 0){
			return i;
		}
	}

	config->names[config->size] = calloc(sizeof(char), strlen(name) + 1);
	strcpy(config->names[config->size], name);
	return config->size++;
}

void configuration_add_rule(struct Configuration *config, char *p1, char *p2, int happiness){
	int i1 = configuration_get_person_index(config, p1);
	int i2 = configuration_get_person_index(config, p2);
	config->happiness[i1][i2] = happiness;
}

struct Configuration *read_configuration(){
	struct Configuration *config = configuration_create(MAX_SIZE);
	char p1[STRING_LEN], p2[STRING_LEN], operation[STRING_LEN];
	int happiness;

	while(scanf("%s would %s %d happiness units by sitting next to %s.", p1, operation, &happiness, p2) != EOF){
		p2[strlen(p2) - 1] = '\0';

		if(strcmp(operation, "gain") == 0){
			configuration_add_rule(config, p1, p2, happiness);
		} else {
			configuration_add_rule(config, p1, p2, -happiness);
		}
	}

	return config;
}

int max(int a, int b){ return(a < b ? b : a); }

int dp(struct Configuration *config, int position, int* arrangement, bool *seated){
	if(position == config->size){
		return config->happiness[arrangement[0]][arrangement[position - 1]]
			+ config->happiness[arrangement[position - 1]][arrangement[0]];
	}

	int i, happiness, solution;

	solution = INT_MIN;
	for(i = 0; i < config->size; i++){
		if(!seated[i]){
			seated[i] = true;
			
			arrangement[position] = i;
			
			if(0 < position){
				happiness = config->happiness[arrangement[position - 1]][i]
					+ config->happiness[i][arrangement[position - 1]];
			} else {
				happiness = 0;
			}
	
			solution = max(solution, happiness + dp(config, position + 1, arrangement, seated));

			seated[i] = false;
		}
	}

	return solution;
}

int solve(struct Configuration *config){
	int i, *arrangement = calloc(sizeof(int), config->size);
	bool *seated = calloc(sizeof(bool), config->size);
	
	for(i = 0; i < config->size; i++){
		seated[i] = false;
		configuration_add_rule(config, config->names[i], "ME", 0);
		configuration_add_rule(config, "ME", config->names[i], 0);
	}

	int solution = dp(config, 0, arrangement, seated);

	free(arrangement);
	free(seated);
	
	return solution;
}

int main(){
	struct Configuration *config = read_configuration();
	printf("%d\n", solve(config));
	configuration_free(config);

	return 0;
}

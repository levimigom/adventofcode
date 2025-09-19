/**
 *	author: levimigom
 *	created: 2025-09-19 20:47:58
 **/
#include <stdio.h>
#include <stdlib.h>

int *read_input(int *size){
	int i, *containers;

	containers = malloc(sizeof(int));
	for(i = 0; scanf("%d", &containers[i]) != EOF; i++){
		containers = realloc(containers, sizeof(int) * (i + 2));
	}

	*size = i;
	return containers;
}

int count_combinations(int *containers, int container_count, int container_index, int liters){
	if(liters == 0){
		return 1;
	}

	if(liters < 0 || container_count == container_index){
		return 0;
	}

	return count_combinations(containers, container_count, container_index + 1, liters - containers[container_index])
	 + count_combinations(containers, container_count, container_index + 1, liters);
}

int main(){
	int container_count, *containers;
	containers = read_input(&container_count);
	
	printf("%d\n", count_combinations(containers, container_count, 0, 150));

	free(containers);

	return 0;
}

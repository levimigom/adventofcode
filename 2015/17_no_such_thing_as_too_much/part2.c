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

int min(int a, int b){ return(a < b ? a : b); }

int minimum_containers(int *containers, int container_count, int container_index, int liters){
	if(liters == 0){
		return 0;
	}

	if(liters < 0 || container_count == container_index){
		return container_count + 1;
	}

	int without_current_container = minimum_containers(containers, container_count, container_index + 1, liters);
	int with_current_container = 1 + minimum_containers(containers, container_count, container_index + 1, liters - containers[container_index]);

	return(min(with_current_container, without_current_container));
}

int count_combinations_with_x_containers(int *containers, int container_count, int container_index, int liters, int usable_containers){
	if(liters == 0 && usable_containers == 0){
		return 1;
	}

	if(liters < 0 || container_count == container_index || usable_containers == 0){
		return 0;
	}

	int without_current_container = count_combinations_with_x_containers(containers, container_count, container_index + 1, liters, usable_containers);
	int with_current_container = count_combinations_with_x_containers(containers, container_count, container_index + 1, liters - containers[container_index], usable_containers - 1);

	return with_current_container + without_current_container;
}

int main(){
	int container_count, min_containers, *containers;
	containers = read_input(&container_count);
	
	min_containers = minimum_containers(containers, container_count, 0, 150);
	printf("%d\n", count_combinations_with_x_containers(containers, container_count, 0, 150, min_containers));

	free(containers);

	return 0;
}

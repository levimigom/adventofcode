#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int compare(const void *a, const void *b){
	int *x = (int*) a;
	int *y = (int*) b;

	return *x - *y;
}

int my_abs(int a){
	return(a < 0 ? -a : a);
}

int main(){
	List *lists[2];
	int i, num, *item;

	lists[0] = list_create(sizeof(int *));
	lists[1] = list_create(sizeof(int *));

	for(i = 0; scanf("%d", &num) != EOF; i++){
		item = malloc(sizeof(int));
		*item = num;

		list_add(lists[i % 2], item);
	}

	list_sort(lists[0], compare);
	list_sort(lists[1], compare);

	int distance, *left, *right;

	for(i = 0, distance = 0; i < lists[0]->count; i++){
		left = (int*) lists[0]->items[i];
		right = (int*) lists[1]->items[i];
		
		distance += my_abs(*left - *right);
	}

	printf("%d\n", distance);

	list_free(lists[0]);
	list_free(lists[1]);
	
	return 0;
}

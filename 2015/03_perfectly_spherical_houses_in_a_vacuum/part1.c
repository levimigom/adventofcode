/**
 *	author: levimigom
 *	created: 2025-08-26 13:48:12
 **/
#include <stdio.h>
#include <stdlib.h>

void move(char c, int *x, int *y){
	switch(c){
		case '^':
			(*x)--;
			break;
		case 'v':
			(*x)++;
			break;
		case '<':
			(*y)--;
			break;
		case '>':
			(*y)++;
			break;
	}
}

void add(int **arr, int pos, int x, int y){
	arr[pos] = calloc(sizeof(int), 2);
	arr[pos][0] = x;
	arr[pos][1] = y;
}

int cmp(const void *elem1, const void *elem2){
	int *l = *((int**) elem1);
	int *r = *((int**) elem2);

	if(l[0] > r[0] || (l[0] == r[0] && l[1] > r[1])){
		return 1;
	}

	if(l[0] == r[0] && l[1] == r[1]){
		return 0;
	}

	return -1;
}

int main(){
	int c, x, y, **arr, arr_size, arr_capacity;
	
	arr_size = arr_capacity = 1;
	arr = calloc(sizeof(int*), arr_capacity);
	add(arr, 0, 0, 0);

	x = y = 0;
	while((c = getchar()) != EOF){
		move(c, &x, &y);
		
		if(arr_size == arr_capacity){
			arr = realloc(arr, sizeof(int*) * (arr_capacity *= 2));
		}

		add(arr, arr_size++, x, y);
	}

	qsort(arr, arr_size, sizeof(int*), cmp);

	int i, unique_houses;

	for(i = unique_houses = 1; i < arr_size; i++){
		if(arr[i][0] != arr[i-1][0] || arr[i][1] != arr[i-1][1]){
			unique_houses++;
		}		
	}
	
	for(i = 0; i < arr_size; i++){
		free(arr[i]);
	}
	free(arr);

	printf("%d\n", unique_houses);

	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#define LIM 100000

int main(){
	List *left;
	int i, num, *item, freq[LIM] = { 0 };

	left = list_create(sizeof(int *));

	for(i = 0; scanf("%d", &num) != EOF; i++){
		if(i % 2 == 0){
			item = malloc(sizeof(int));
			*item = num;

			list_add(left, item);
		} else {
			freq[num]++;
		}
	}

	int similarity_score;

	for(i = similarity_score = 0; i < left->count; i++){
		item = (int*) left->items[i];

		similarity_score += *item * freq[*item]; 
	}

	printf("%d\n", similarity_score);

	list_free(left);
	
	return 0;
}

/**
 *	author: levimigom
 *	created: 2025-12-03 16:36:58
 **/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define LEN 32
#define SIZE 1024

bool contains(long *arr, int size, long value){
	int i;

	for(i = 0; i < size; i++){
		if(arr[i] == value){
			return true;
		}
	}

	return false;
}

void add_invalid_ids(long from, long to, int* invalid_ids_count, long *invalid_ids){
	int i, j;
	long x;
	char s[LEN];
	
	x = 0;
	for(i = 1; x <= to; i++){
		sprintf(s, "%d%d", i, i);
		x = atol(s);
	
		while(x <= to){
			if(from <= x && x <= to && !contains(invalid_ids, *invalid_ids_count, x)){
				invalid_ids[(*invalid_ids_count)++] = x;
			}

			sprintf(s, "%.16s%d", s, i);
			x = atol(s);
		}

		sprintf(s, "%d%d", i, i);
		x = atol(s);
	} 
}

void solve(){
	int c, i, invalid_ids_count;
	long range[2], sum, invalid_ids[SIZE];

	i = range[0] = range[1] = invalid_ids_count = 0;
	while((c = getchar()) != EOF && c != '\n'){
		switch(c){
			case ',':
				add_invalid_ids(range[0], range[1], &invalid_ids_count, invalid_ids);
				i = range[0] = range[1] = 0;
				break;
			case '-':
				i++;
				break;
			default:
				range[i] = range[i] * 10 + c - '0';
				break;
		}
	}

	add_invalid_ids(range[0], range[1], &invalid_ids_count, invalid_ids);
	
	sum = 0;
	for(i = 0; i < invalid_ids_count; i++) sum += invalid_ids[i];
	printf("%ld\n", sum);
}

int main(){
	solve();
	return 0;
}

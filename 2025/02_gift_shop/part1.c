/**
 *	author: levimigom
 *	created: 2025-12-03 16:36:58
 **/
#include <stdio.h>
#include <stdlib.h>
#define LEN 32

long invalid_ids_sum(long from, long to){
	int i;
	long x, sum;
	char s[LEN];
	
	x = sum = 0;
	for(i = 1; x <= to; i++){
		sprintf(s, "%d%d", i, i);
		x = atol(s);

		if(from <= x && x <= to){
			sum += x;	
		}
	} 

	return sum;
}

void solve(){
	int c, i;
	long range[2], sum;

	i = range[0] = range[1] = sum = 0;
	while((c = getchar()) != EOF && c != '\n'){
		switch(c){
			case ',':
				sum += invalid_ids_sum(range[0], range[1]);
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

	sum += invalid_ids_sum(range[0], range[1]);
	printf("%ld\n", sum);
}

int main(){
	solve();
	return 0;
}

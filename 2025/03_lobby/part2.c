/**
 *	author: levimigom
 *	created: 2025-12-03 16:02:52
 **/
#include <stdio.h>
#include <string.h>
#define LEN 128
#define BATTERIES 12

int max_index(char *s, int from, int to){
	int i, j;

	for(i = j = from; i < to; i++){
		if(s[j] < s[i]){
			j = i;
		}
	}

	return j;
}

long max_joltage(char *s){
	int i, j;
	long joltage;

	j = max_index(s, 0, strlen(s) - BATTERIES + 1);
	joltage = s[j] - '0';
	for(i = 2; i <= BATTERIES; i++){
		j = max_index(s, j + 1, strlen(s) - BATTERIES + i);
		joltage = 10 * joltage + s[j] - '0';
	}

	return joltage;	
}

int main(){
	char bank[LEN];
	long sum;

	sum = 0;
	while(scanf("%s", bank) != EOF){
		printf("%ld\n", max_joltage(bank));
		sum += max_joltage(bank);
	}

	printf("%ld\n", sum);

	return 0;
}

/**
 *	author: levimigom
 *	created: 2025-12-03 16:02:52
 **/
#include <stdio.h>
#define LEN 128

int max_joltage(char *s){
	int i, j, k;
	
	for(i = j = 0; s[i + 1] != '\0'; i++){
		if(s[j] < s[i]){
			j = i;
		}
	}

	for(i = k = j + 1; s[i] != '\0'; i++){
		if(s[k] < s[i]){
			k = i;
		}
	}

	return 10 * (s[j] - '0') + s[k] - '0';
}

int main(){
	char bank[LEN];
	int sum;

	sum = 0;
	while(scanf("%s", bank) != EOF){
		sum += max_joltage(bank);
	}

	printf("%d\n", sum);

	return 0;
}

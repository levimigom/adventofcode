/**
 *	author: levimigom
 *	created: 2025-08-31 20:06:00
 **/
#include <stdio.h>

int main(){
	int c, previous, number, sum;

	sum = 0;
	previous = -1;
	while((c = getchar()) != EOF){
		if('0' <= c && c <= '9'){
			number = c - '0';

			while((c = getchar()) != EOF && '0' <= c && c <= '9'){
				number = (10 * number) + c - '0';
			}
		
			if(previous == '-'){
				sum -= number;
			} else {
				sum += number;
			}
		}

		previous = c;
	}

	printf("%d\n", sum);

	return 0;
}

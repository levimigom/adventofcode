/**
 *	author: levimigom
 *	created: 2025-12-01 11:15:50
 **/
#include <stdio.h>
#include <stdlib.h>
#define LEN 8
#define MOD 100

int main(){
	char rotation[LEN];
	int dial_position, new_dial_position, distance, zero_count;

	zero_count = 0;
	dial_position = 50;
	while(scanf("%s", rotation) != EOF){
		distance = atoi(rotation + 1);
		
		zero_count += distance / MOD;
		distance %= MOD;

		if(rotation[0] == 'L'){
			distance *= -1;
		}

		new_dial_position = (dial_position + distance + MOD) % MOD;
		
		if(rotation[0] == 'L' && (new_dial_position == 0 || (dial_position < new_dial_position && dial_position != 0))){
			zero_count ++;
		} else if(rotation[0] == 'R' && (new_dial_position < dial_position)){
			zero_count++;
		}
		
		dial_position = new_dial_position;
	}

	printf("%d\n", zero_count);

	return 0;
}
